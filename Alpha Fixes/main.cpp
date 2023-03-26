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
	info->version = 232;
	return true;
}

// TODO
// Fix alpha blending issues when two alpha blended objects overlap
// Die in the process

#define BSRenderState_StateStatus *(UInt32*)0x11FFA28
#define GPUVendor *(UInt32*)0x11F94B8

void(__cdecl* SetShaderPackage)(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) = (void(__cdecl*)(int, int, bool, int, char*, int))0xB4F710;
void(__cdecl* SetShaderPackageGECK)(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) = (void(__cdecl*)(int, int, bool, int, char*, int))0x8F8670;

void(__cdecl* SetAlphaBlendEnable)(int, int) = (void(__cdecl*)(int, int))0xB97FA0;
void(__cdecl* SetSrcAndDstBlends)(int, int, int) = (void(__cdecl*)(int, int, int))0xB97FF0;

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
bool bIsGeck = 0;

// Reports GPU as Nvidia - Game forcibly disables TMSAA on Intel, despite it supporting ATOC format nowadays (kinda jank tho)
void __cdecl SetShaderPackageHook(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) {
	_MESSAGE("[SetShaderPackageHook] User has a %s GPU", gpuVendor);
	if (_strnicmp(gpuVendor, "nv", 2) && _strnicmp(gpuVendor, "at", 2)) {
		_MESSAGE("[SetShaderPackageHook] GPU \"doesn't support\" TMSAA - spoofing as Nvidia");
		gpuVendor = (char*)"nv";
	};
	if (bIsGeck) {
		SetShaderPackageGECK(PixelShader, VertexShader, bForce1XShaders, checkVendors, gpuVendor, NumInstructionSlots);
	}
	else {
		SetShaderPackage(PixelShader, VertexShader, bForce1XShaders, checkVendors, gpuVendor, NumInstructionSlots);
	}
}

D3DFORMAT TMSAA_Format;
D3DRENDERSTATETYPE TMSAA_StateType;
int bInternalStatus = 0;

// Controls the Transparency Multisampling state based on the pass, preventing broken or barely visible effects
// Vanilla function has similar issue to the alpha blending one, where it is unable to reset the state due to a faulty check
// That's why disintegration effects are broken - they're using the TMSAA from the previous pass
// Additionally, TMSAA is being enabled on the last pass in the group for whatever reason, thus the need to handle them manually
void __cdecl SetTMSAAState(int bEnable, int bMarkStatus) {
	// Quit early if state is same as before
	if (bInternalStatus == bEnable) {
		BSRenderState_StateStatus += bMarkStatus;
		return;
	}

	if (bEnable) {
		const BSRenderPass* pCurrentPass = BSRenderPass::GetCurrentPass();
		UInt32 passType = 0;
		bool bCandidatePass = 0;

		// Yes, that bEnabled needs to be checked against one. Not an error. If it's above 1, then it doesn't have geometry.
		if (pCurrentPass && pCurrentPass->bEnabled == 1) {
			passType = pCurrentPass->usPassEnum;
			bCandidatePass = true;
		}
		else {
			passType = BSRenderPass::GetCurrentPassType();
		}
		if (passType > 0 && passType < BSSM_TILE) {
			switch (passType) {
				// These passes have no importance for us
			case BSSM_AMBIENT_OCCLUSION:
			case BSSM_SKYBASEPRE:
			case BSSM_SKY:
			case BSSM_SKY_TEXTURE:
			case BSSM_SKY_CLOUDS:
			case BSSM_SKYBASEPOST:
				break;
				// These passes break with TMSAA
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
				bEnable = 0;
				break;
			default:
				// Check for "No_Transparency_Multisampling"
				if (bCandidatePass && pCurrentPass->pGeometry) {
					const NiGeometry* pGeo = pCurrentPass->pGeometry;
					if (pGeo) {
						const BSShaderProperty* shaderProp = (BSShaderProperty*)pGeo->shaderProperties.m_shadeProperty;
						if (shaderProp) {
#if _DEBUG
							_MESSAGE("[AlphaMSAA] [Default] [TMSAA check] Current pass: %i | %s | %s", passType, BSRenderPass::GetPassName(passType), BSRenderPass::GetCurrentPassName());
							_MESSAGE("[AlphaMSAA] [Default] [TMSAA check] Shader type: %s", BSRenderPass::GetCurrentPassShaderType());
							const char* model = GetModelPath(FindReferenceFor3D((NiNode*)pGeo));
							_MESSAGE("[AlphaMSAA] [Default] [TMSAA check] Current geo: %s, %s", pGeo->m_pkParent->m_kName, model ? model : "Unknown");
#endif
							if (shaderProp->m_eShaderType != -1) {
								if ((shaderProp->BSShaderFlags[1] & BSShaderProperty::kFlags2_No_Transparency_Multisampling) != 0) {
#if _DEBUG
									_MESSAGE("[AlphaMSAA] [Default] [TMSAA check] Disabling...");
#endif
									bEnable = 0;
									break;
								}
							}
						}
					}
				}
				break;
			}
		}
	}

	// Recheck in change we updated the value
	if (bInternalStatus == bEnable) {
		BSRenderState_StateStatus += bMarkStatus;
		return;
	}

	if (GPUVendor == 2) {
		TMSAA_StateType = D3DRS_POINTSIZE;
		if (bEnable) {
			TMSAA_Format = (D3DFORMAT)MAKEFOURCC('A', '2', 'M', '1');
		}
		else {
			TMSAA_Format = (D3DFORMAT)MAKEFOURCC('A', '2', 'M', '0');
		}
	}
	else {
		TMSAA_StateType = D3DRS_ADAPTIVETESS_Y;
		if (bEnable) {
			TMSAA_Format = (D3DFORMAT)MAKEFOURCC('A', 'T', 'O', 'C');
		}
		else {
			TMSAA_Format = D3DFMT_UNKNOWN;
		}
	}
	SetRenderState(NiDX9Renderer::Get()->m_pkRenderState, TMSAA_StateType, TMSAA_Format, 0, 0);
	BSRenderState_StateStatus += bMarkStatus;
	bInternalStatus = bEnable;
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
		_MESSAGE("[SetBlendAlpha] Current pass: %s, shader type: %s", BSRenderPass::GetCurrentPassName(), shadeProp->GetShaderType());
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
		for (UInt32 callAddr : { 0x10AF378, 0x10AF7E0, 0x10AFA60, 0x10AFE98, 0x10B0040, 0x10B0218, 0x10B03B8, 0x10B0598, 0x10B0740, 0x10B08E0, 0x10B0A80, 0x10B0C18, 0x10B0DC0, 0x10B0F40, 0x10B10C0, 0x10B1240, 0x10B13C0, 0x10B1540, 0x10B16C0, 0x10B1878, 0x10B1A00, 0x10B1B88, 0x10B1D10, 0x10B1EA0, 0x10B2030, 0x10B21C0, 0x10B2388, 0x10B2510, 0x10B2690, 0x10B2828, 0x10B29A0, 0x10B2B18, 0x10B2C90, 0x10B2E30, 0x10B2FD0, 0x10B3160, 0x10B32E8, 0x10B3470, 0x10B3618, 0x10B3828, 0x10B39D8, 0x10B3B70, 0x10B3CF8, 0x10B3E98, 0x10B4028, 0x10B41B8, 0x10B4348, 0x10B44E0, 0x10B4680, 0x10B4820, 0x10B49B8, 0x10B4B50, 0x10B4CE8, 0x10B4E68, 0x10B5000, 0x10B51C0, 0x10B5340, 0x10B5500, 0x10B56C0, 0x10B5850, 0x10B59F8, 0x10B5B90, 0x10B5D38, 0x10B5F28, 0x10B60C8, 0x10B6270, 0x10B6418, 0x10B65C8, 0x10B6770, 0x10B6920, 0x10B6AC0, 0x10B6C58, 0x10B6E10, 0x10B6FB8, 0x10B7158, 0x10B72F8, 0x10B7498, 0x10B7618, 0x10B77A0, 0x10B7938, 0x10B7AD0, 0x10B7C70, 0x10B8A00, 0x10B8F00, 0x10B9210, 0x10B9B28, 0x10BA430, 0x10BAE18, 0x10BAFE0, 0x10BB490, 0x10BB608, 0x10BB828, 0x10BBA00, 0x10BBBD0, 0x10BBD88, 0x10BBF38, 0x10BC0F0, 0x10BC2E0, 0x10BC698, 0x10BC978, })
		{
			SafeWrite32(callAddr, UInt32(SetBlendAlpha));
		}
		WriteRelJump(0xBBC5FD, SetBlendAlpha);
		WriteRelCall(0xBC8F0B, SetBlendAlpha);

		for (UInt32 callAddr : {0x714C54, 0xB9956C, 0xB99FAF, 0xB9A004, 0xB9A00E, 0xB9A187, 0xB9A1AB, 0xB9A1E0, 0xB9A215, 0xB9A24A, 0xB9A37E, 0xB9A38A, }) {
			WriteRelCall(callAddr, SetTMSAAState);
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