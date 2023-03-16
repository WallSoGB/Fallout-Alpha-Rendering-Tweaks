#pragma comment(lib, "d3dx9.lib")
#include "nvse/PluginAPI.h"
#include <windows.h>
#include <SafeWrite.h>
#include <GameData.h>
#include <fstream>
#include <string>
#include <decoded.h>
#include "d3d9.h"

NVSEInterface* g_nvseInterface{};
IDebugLog	   gLog("logs\\FART.log");

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Fallout Alpha Rendering Tweaks";
	info->version = 2;
	return true;
}

// TODO
// Fix alpha blending issues when two alpha blended objects overlap
// Die in the process

UInt32* BSRenderState_StateStatus = (UInt32*)0x11FF9D8;

void(__cdecl* SetShaderPackage)(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) = (void(__cdecl*)(int, int, bool, int, char*, int))0xB4F710;
void(__cdecl* SetShaderPackageGECK)(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) = (void(__cdecl*)(int, int, bool, int, char*, int))0x8F8670;

void(__cdecl* SetAlphaBlendEnable)(int, int) = (void(__cdecl*)(int, int))0xB97FA0;
void(__cdecl* SetSrcAndDstBlends)(int, int, int) = (void(__cdecl*)(int, int, int))0xB97FF0;
void(__cdecl* SetTransparencyMultisampling)(int, int) = (void(__cdecl*)(int, int))0xB98540;

void(__thiscall* SetRenderState)(int*, D3DRENDERSTATETYPE eState, unsigned int uiValue, int a4, bool bSave) = (void(__thiscall*)(int*, D3DRENDERSTATETYPE eState, unsigned int uiValue, int a4, bool bSave))0xE88780;

#if _DEBUG
TESObjectREFR* (__cdecl* FindReferenceFor3D)(NiNode* node) = (TESObjectREFR * (__cdecl*)(NiNode*))0x56F930;

const char* GetModelPath(TESObjectREFR* ref) {
	if (!ref)
		return "Not a ref";

	TESForm* form = ref->baseForm;

	if (TESModel* model = DYNAMIC_CAST(form, TESForm, TESModel))
		return model->nifPath.m_data ? model->nifPath.m_data : "No nif";
}
#endif

// SSAA - does it even work? I see no visual difference. Also - no DXVK compat so uhhhh
#if _SSAA
bool bUseSSAA = 0;
bool bCanUseSSAA = 0;
#endif
bool bIsGeck = 0;

// Reports GPU as Nvidia - Game forcibly disables TMSAA on Intel, despite it supporting ATOC format nowadays (kinda jank tho)
void __cdecl SetShaderPackageHook(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) {
	_MESSAGE("[SetShaderPackageHook] User has a %s GPU", gpuVendor);
	if (!_strnicmp(gpuVendor, "ig", 2)) {
		_MESSAGE("[SetShaderPackageHook] User has an Intel GPU - spoofing as Nvidia");
		gpuVendor = (char*)"nv";
	};
#if _SSAA
	if (bUseSSAA) {
		HRESULT result = (*(LPDIRECT3D9*)0x126F0D8)->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_SURFACE, (D3DFORMAT)MAKEFOURCC('S', 'S', 'A', 'A'));
		if (result == S_OK) {
			_MESSAGE("SSAA supported");
			bCanUseSSAA = 1;
		}
		else {
			_MESSAGE("SSAA not supported");
			bCanUseSSAA = 0;
		}
	}
#endif
	if (bIsGeck) {
		SetShaderPackageGECK(PixelShader, VertexShader, bForce1XShaders, checkVendors, gpuVendor, NumInstructionSlots);
	}
	else {
		SetShaderPackage(PixelShader, VertexShader, bForce1XShaders, checkVendors, gpuVendor, NumInstructionSlots);
	}
}

// Manually force disable and set status to prevent overflow (game doesn't always reset it)
void __forceinline DisableTransparencyMultisampling(bool markStatus) {
	SetTransparencyMultisampling(0, 0);
	if (markStatus) {
		BSRenderState_StateStatus[20] = 1;
	}
}

#if _SSAA
// Switch to SSAA if applicable
void SetSSAA(int bEnable, int markStatus) {
	if (BSRenderState_StateStatus[20]) {
		BSRenderState_StateStatus[20] += markStatus;
		return;
	}
	D3DFORMAT enableSSAA;
	if (bEnable == BSRenderState_StateStatus[20])
	{
		enableSSAA = D3DFMT_UNKNOWN;
	}
	else
	{
		enableSSAA = (D3DFORMAT)MAKEFOURCC('S', 'S', 'A', 'A');
#if _DEBUG
		_MESSAGE("[SetSSAA] Using SSAA for pass: %s, shader type: %s", BSRenderPass::GetCurrentPassName(), BSRenderPass::GetCurrentPassShaderType(), bEnable);
#endif
	}
	SetRenderState(((*(int**)0x11C73B4) + 0x8B8), D3DRS_ADAPTIVETESS_Y, enableSSAA, 0, 0);
	BSRenderState_StateStatus[20] += markStatus;
}
#endif

// Controls the Transparency Multisampling state based on the pass, preventing broken TexEffect animations
// TODO
// Add some AA pass. SMAA or FXAA?
void __cdecl AlphaMSAA(int bEnable, int markStatus) {
	// No need to do anything if it's getting disabled
	if (!bEnable) {
		SetTransparencyMultisampling(bEnable, markStatus);
		return;
	}

	static const BSRenderPass* pCurrentPass = BSRenderPass::GetCurrentPass();
	static UInt16 passType = 0;
	if (pCurrentPass && pCurrentPass->bEnabled) {
		passType = pCurrentPass->usPassEnum;
	}
	if (!passType)
		passType = BSRenderPass::GetCurrentPassType();

	// Some PipBoy stuff is above 758 - Local maps?
	if (passType > BSSM_IMAGESPACE) {
		SetTransparencyMultisampling(bEnable, markStatus);
		return;
	}
#if _DEBUG
	_MESSAGE("[AlphaMSAA] Current pass: %s, shader type: %s, TMSAA request: %i", BSRenderPass::GetCurrentPassName(), BSRenderPass::GetCurrentPassShaderType(), bEnable);
#endif

	switch (passType) {
		// Complete no-no list, don't bother with doing anything else
	case 0:
	case BSSM_AMBIENT_OCCLUSION:
	case BSSM_SKYBASEPRE:
	case BSSM_SKY:
	case BSSM_SKY_TEXTURE:
	case BSSM_SKYBASEPOST:
	case BSSM_TILE:
	case BSSM_IMAGESPACE:
		SetTransparencyMultisampling(bEnable, markStatus);
		break;
		// These passes get broken visuals with TMSAA
	case BSSM_ZONLY:
	case BSSM_ZONLY_S:
	case BSSM_ZONLY_TEXEFFECT:
	case BSSM_ZONLY_TEXEFFECT_S:
	case BSSM_3XZONLY_TEXEFFECT:
	case BSSM_3XZONLY_TEXEFFECT_S:
	case BSSM_NOLIGHTING_PSYS:
	case BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET:
	case BSSM_NOLIGHTING_PSYS_PREMULT_ALPHA:
	case BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET_PREMULT_ALPHA:
	case BSSM_NOLIGHTING_STRIP_PSYS:
	case BSSM_NOLIGHTING_STRIP_PSYS_SUBTEX:
	case BSSM_3XTEXEFFECT:
	case BSSM_3XTEXEFFECT_S:
	case BSSM_2x_TEXEFFECT:
	case BSSM_2x_TEXEFFECT_S:
#if _SSAA
		if (bCanUseSSAA)
			SetSSAA(bEnable, markStatus);
		else
#endif
#if _DEBUG
			if (pCurrentPass)
				if (pCurrentPass->bEnabled) {
					if (pCurrentPass->pGeometry) {
						NiGeometry* pGeo = pCurrentPass->pGeometry;
						if (pGeo) {
							const char* model = GetModelPath(FindReferenceFor3D((NiNode*)pGeo));
							_MESSAGE("[AlphaMSAA] Current geo: %s, %s | Pass: %s, shader type: %s, TMSAA request: %i", pGeo->m_pkParent->m_kName, model = model ? model : "Unknown", BSRenderPass::GetCurrentPassName(), BSRenderPass::GetCurrentPassShaderType(), bEnable);
						}
					}
				}
#endif
		DisableTransparencyMultisampling(markStatus);
		break;
	default:
		// Check for "No_Transparency_Multisampling"
		// That's a lot of checks, whew
#if _DEBUG
		_MESSAGE("[AlphaMSAA] Current pass: %s, shader type: %s, TMSAA request: %i", BSRenderPass::GetCurrentPassName(), BSRenderPass::GetCurrentPassShaderType(), bEnable);
#endif
		if (pCurrentPass && pCurrentPass->bEnabled) {
			if (NiGeometry* pGeo = pCurrentPass->pGeometry) {
				if (BSShaderProperty* shaderProp = (BSShaderProperty*)pGeo->shaderProperties.m_shadeProperty) {
					if (shaderProp->m_eShaderType != -1) {
						if ((shaderProp->BSShaderFlags[1] & BSShaderProperty::kFlags2_No_Transparency_Multisampling) != 0) {
							DisableTransparencyMultisampling(markStatus);
							break;
						}
					}
				}
			}
		}
		SetTransparencyMultisampling(bEnable, markStatus);
		break;
	}
}

// This one's cool.
// Game doesn't reset the render state, so objects *not* having alpha blending inherit the state from the one that did.
// Game also breaks if you use No_Fade flag in combination with NiAlphaController modifying fAlpha, causing it to flicker. (One disables alpha, and the other one sets it. Every frame.)
void __fastcall SetBlendAlpha(BSShader* thiss, void*, NiGeometry::ShaderProperties* shaderProps)
{
	SetAlphaBlendEnable(0, 0);
	BSShaderProperty* shadeProp = (BSShaderProperty*)shaderProps->m_shadeProperty;
	if (!shadeProp || shadeProp->m_eShaderType == -1) {
		return;
	}
	NiAlphaProperty* alphaProp = shaderProps->m_alphaProperty;
	unsigned short flags = alphaProp ? alphaProp->m_usFlags : 0;
	bool bBlend = (flags & 1) != 0;
	bool bEnableBlend = ((shadeProp->fAlpha < 1.0f && ((shadeProp->BSShaderFlags[1] & BSShaderProperty::kFlags2_No_Fade) == 0)) || shadeProp->fFadeAlpha < 1.0f || bBlend);
	if (bEnableBlend) {
#if _DEBUG
		//	_MESSAGE("[SetBlendAlpha] Current pass: %s, shader type: %s", BSRenderPass::GetCurrentPassName(), shadeProp->GetShaderType());
#endif
		SetAlphaBlendEnable(1, 0);
		if (bBlend) {
			SetSrcAndDstBlends(((flags >> 1) & 0xF), ((flags >> 5) & 0xF), 0);
		}
		else {
			SetSrcAndDstBlends(6, 7, 0);
		}
	}
}

// Thx karut for help with jumping
// Fixes a flag check for Transparency Multisampling to check for both blending and testing values
// Vanilla simply goes "Does mesh have testing enabled?", "Yes?", "Great! Now it will be forcibly using TMSAA breaking your stuff because it's meant for alpha blending"
__declspec (naked) void AlphaMalding() {
	static const uintptr_t kDisable = 0xB99568;
	static const uintptr_t kEnable = 0xB99562;
	__asm {
		mov ax, [eax + 0x18]
		test ax, 0x200 // Alpha Test... test
		jz itsOver
		test ax, 1 // Alpha Blend test
		jz itsOver
		jmp kEnable
		itsOver :
		jmp kDisable
	}
}

bool NVSEPlugin_Load(NVSEInterface* nvse) {
	if (!nvse->isEditor) {
#if _SSAA
		char iniDir[MAX_PATH];
		GetModuleFileNameA(GetModuleHandle(NULL), iniDir, MAX_PATH);
		strcpy((char*)(strrchr(iniDir, '\\') + 1), "Data\\NVSE\\Plugins\\FART.ini");
		bUseSSAA = GetPrivateProfileInt("Main", "bUseSSAA", 0, iniDir);
#endif

		for (UInt32 callAddr : { 0x10AF378, 0x10AF7E0, 0x10AFA60, 0x10AFE98, 0x10B0040, 0x10B0218, 0x10B03B8, 0x10B0598, 0x10B0740, 0x10B08E0, 0x10B0A80, 0x10B0C18, 0x10B0DC0, 0x10B0F40, 0x10B10C0, 0x10B1240, 0x10B13C0, 0x10B1540, 0x10B16C0, 0x10B1878, 0x10B1A00, 0x10B1B88, 0x10B1D10, 0x10B1EA0, 0x10B2030, 0x10B21C0, 0x10B2388, 0x10B2510, 0x10B2690, 0x10B2828, 0x10B29A0, 0x10B2B18, 0x10B2C90, 0x10B2E30, 0x10B2FD0, 0x10B3160, 0x10B32E8, 0x10B3470, 0x10B3618, 0x10B3828, 0x10B39D8, 0x10B3B70, 0x10B3CF8, 0x10B3E98, 0x10B4028, 0x10B41B8, 0x10B4348, 0x10B44E0, 0x10B4680, 0x10B4820, 0x10B49B8, 0x10B4B50, 0x10B4CE8, 0x10B4E68, 0x10B5000, 0x10B51C0, 0x10B5340, 0x10B5500, 0x10B56C0, 0x10B5850, 0x10B59F8, 0x10B5B90, 0x10B5D38, 0x10B5F28, 0x10B60C8, 0x10B6270, 0x10B6418, 0x10B65C8, 0x10B6770, 0x10B6920, 0x10B6AC0, 0x10B6C58, 0x10B6E10, 0x10B6FB8, 0x10B7158, 0x10B72F8, 0x10B7498, 0x10B7618, 0x10B77A0, 0x10B7938, 0x10B7AD0, 0x10B7C70, 0x10B8A00, 0x10B8F00, 0x10B9210, 0x10B9B28, 0x10BA430, 0x10BAE18, 0x10BAFE0, 0x10BB490, 0x10BB608, 0x10BB828, 0x10BBA00, 0x10BBBD0, 0x10BBD88, 0x10BBF38, 0x10BC0F0, 0x10BC2E0, 0x10BC698, 0x10BC978, })
		{
			SafeWrite32(callAddr, UInt32(SetBlendAlpha));
		}
		WriteRelJump(0xBBC5FD, SetBlendAlpha);
		WriteRelCall(0xBC8F0B, SetBlendAlpha);

		for (UInt32 callAddr : {0x714C54, 0xB9956C, 0xB99FAF, 0xB9A004, 0xB9A00E, 0xB9A187, 0xB9A1AB, 0xB9A1E0, 0xB9A215, 0xB9A24A, 0xB9A37E, 0xB9A38A, }) {
			WriteRelCall(callAddr, AlphaMSAA);
		}

		WriteRelJump(0xB99556, (UInt32)AlphaMalding);

		WriteRelCall(0x4DB187, (UInt32)SetShaderPackageHook);
		WriteRelCall(0x4DCB9D, (UInt32)SetShaderPackageHook);
	}
	else {
		bIsGeck = 1;
		WriteRelCall(0x429D5B, SetShaderPackageHook);
		WriteRelCall(0x53198B, SetShaderPackageHook);
	}

	return true;
}