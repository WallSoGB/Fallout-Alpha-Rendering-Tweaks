#pragma comment(lib, "d3dx9.lib")
#include "nvse/PluginAPI.h"
#include "SafeWrite.h"
#include "BSBatchRenderer.hpp"
#include "NiDX9Renderer.hpp"
#include "NiPropertyState.hpp"
#include "NiAlphaProperty.hpp"
#include "NiGeometry.hpp"
#include "NiStencilProperty.hpp"
#include "NiBound.hpp"
#include "NiCamera.hpp"

NVSEInterface* g_nvseInterface{};
IDebugLog	   gLog("logs\\FART.log");

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Fallout Alpha Rendering Tweaks";
	info->version = 251;
	return true;
}

// TODO
// Fix alpha blending issues when two alpha blended objects overlap
// Die in the process

void(__cdecl* SetShaderPackage)(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) = (void(__cdecl*)(int, int, bool, int, char*, int))0xB4F710;
void(__cdecl* SetShaderPackageGECK)(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) = (void(__cdecl*)(int, int, bool, int, char*, int))0x8F8670;

void(__cdecl* SetAlphaBlendEnable)(int, int) = (void(__cdecl*)(int, int))0xB97FA0;
void(__cdecl* SetSrcAndDstBlends)(int, int, int) = (void(__cdecl*)(int, int, int))0xB97FF0;

bool bIsGeck = 0;
static bool bForcePatchParticles;


// Reports GPU as Nvidia - Game forcibly disables TMSAA on Intel (any non Nvidia or AMD GPU tbh), despite it supporting ATOC format nowadays
void __cdecl SetShaderPackageHook(int PixelShader, int VertexShader, bool bForce1XShaders, int checkVendors, char* gpuVendor, int NumInstructionSlots) {
	_MESSAGE("[ SetShaderPackageHook ] User has a %s GPU", gpuVendor);
	if (_strnicmp(gpuVendor, "nv", 2) && _strnicmp(gpuVendor, "at", 2)) {
		if (NiDX9Renderer::GetD3D9()->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_SURFACE, (D3DFORMAT)MAKEFOURCC('A', 'T', 'O', 'C')) == S_OK) {
			_MESSAGE("[ SetShaderPackageHook ] Unknown GPU supports TMSAA - spoofing as Nvidia");
			gpuVendor = (char*)"nv";
		}
	};
	if (bIsGeck) {
		SetShaderPackageGECK(PixelShader, VertexShader, bForce1XShaders, checkVendors, gpuVendor, NumInstructionSlots);
	}
	else {
		SetShaderPackage(PixelShader, VertexShader, bForce1XShaders, checkVendors, gpuVendor, NumInstructionSlots);
	}
}

SInt32 PassSort(UInt16 pass1, UInt16 pass2) {
	return pass1 < pass2 ? -1 : 1;
}


// Main fix for TMSAA
// Game checks for TexEffect passes and... specifically assigns them a group that is destined to use TMSAA. Mistake?
void __fastcall RegisterPassGeometryGroup(BSBatchRenderer* apThis, void*, BSShaderProperty::RenderPass* apRenderPass, BSShaderManager::RenderPassType auiPassEnum) {
	if (!apRenderPass)
		return;

	NiGeometry* pGeom = apRenderPass->pGeometry;
	if (!apRenderPass->pGeometry)
		return;

	UInt32 eAlphaType = BSBatchRenderer::ALPHA_NONE;
	bool bHasStencil = false;
	BSShaderProperty* pShaderProp = pGeom->GetShadeProperty<BSShaderProperty>();
	NiStencilProperty* pStencilProp = pGeom->GetStencilProperty();
	if (pStencilProp && pStencilProp->m_usFlags.IsSet(NiStencilProperty::DRAWMODE_MASK)) {
		bHasStencil = true;
	}
	NiAlphaProperty* pAlphaProp = pGeom->GetAlphaProperty();
	bool bUseAlphaTest = false;
	if (pAlphaProp) {
		bUseAlphaTest = true;

		if (!pAlphaProp->HasAlphaTest() || !apRenderPass->bEnabled) {
			bUseAlphaTest = false;
		}

		if ((pShaderProp->fAlpha < 1.f || pShaderProp->fFadeAlpha < 1.f) && !pAlphaProp->HasAlphaBlend() && auiPassEnum != BSShaderManager::BSSM_ZONLY_At) {
			bUseAlphaTest = true;
		}
	}

	if (!bUseAlphaTest && auiPassEnum == BSShaderManager::BSSM_SKY_MOON_STARS_MASK)
		bUseAlphaTest = true;

	// At this point vanilla would set `bUseAlphaTest = true` for TEXEFFECT passes, which enables TMSAA in every scenario.
	switch (auiPassEnum) {
	case BSShaderManager::BSSM_ZONLY_TEXEFFECT:
	case BSShaderManager::BSSM_ZONLY_TEXEFFECT_S:
	case BSShaderManager::BSSM_3XZONLY_TEXEFFECT:
	case BSShaderManager::BSSM_3XZONLY_TEXEFFECT_S:
	case BSShaderManager::BSSM_PARTICLE:
	case BSShaderManager::BSSM_PARTICLE_PREPASS:
	case BSShaderManager::BSSM_TEXEFFECT:
	case BSShaderManager::BSSM_TEXEFFECT_S:
	case BSShaderManager::BSSM_2x_TEXEFFECT:
	case BSShaderManager::BSSM_2x_TEXEFFECT_S:
		eAlphaType = BSBatchRenderer::ALPHA_NO_TMSAA;
		break;
	default:
		if (pShaderProp->HasNoTMSAA()) {
			eAlphaType = BSBatchRenderer::ALPHA_NO_TMSAA;
		}
		else if (bUseAlphaTest) {
			eAlphaType = bHasStencil ? BSBatchRenderer::ALPHA_TEST_STENCIL : BSBatchRenderer::ALPHA_TEST_NO_STENCIL;
		}
		else {
			eAlphaType = bHasStencil ? BSBatchRenderer::ALPHA_STENCIL : BSBatchRenderer::ALPHA_NONE;
		}
		break;
	}

	BSShaderManager::RenderPassType uiCurrentPass = static_cast<BSShaderManager::RenderPassType>(apRenderPass->usPassEnum);
	UInt32 uiGroup;
	if (auiPassEnum)
		uiCurrentPass = auiPassEnum;
	if (!apThis->kPassMap.GetAt(uiCurrentPass, uiGroup)) {
		uiGroup = apThis->kPassMap.GetCount();
		apThis->kPassMap.SetAt(uiCurrentPass, uiGroup);
		ThisStdCall(0xB99A50, &apThis->pAccumStructures4[uiGroup], 0);
	}

	if (!apThis->pAccumStructures4[uiGroup].uiCount)
		ThisStdCall(0xB99770, &apThis->kCurrentBatch, uiCurrentPass, PassSort);

	if (apRenderPass->bEnabled && (uiCurrentPass < BSShaderManager::BSSM_SKYBASEPRE || uiCurrentPass > BSShaderManager::BSSM_SKY_CLOUDS_UNDERWATER))
		apThis->pAccumStructures4[uiGroup].AddHead(eAlphaType, apRenderPass);
	else
		apThis->pAccumStructures4[uiGroup].AddTail(eAlphaType, apRenderPass);
}

// RenderPassImmediately does not use alpha defined by RegisterPassGeometryGroup (odd), so we need to add TMSAA check here as well.
void __cdecl CheckFlags(bool abEnable, bool abCount) {
	BSShaderProperty::RenderPass* pPass = BSShaderProperty::RenderPass::GetCurrentPass();
	BSShaderProperty* pShaderProp = pPass->pGeometry->GetShadeProperty<BSShaderProperty>();

	bool bForceDisable = false;
	if (bForcePatchParticles) { // Disable TMSAA for particles as it makes them *super* faint.
		bForceDisable = pPass->pGeometry->IsParticlesGeom();
	}

	if (pShaderProp->HasNoTMSAA() || bForceDisable)
		CdeclCall(0xB98540, false, abCount);
	else {
		CdeclCall(0xB98540, abEnable, abCount);
	}
}

SInt32 __cdecl AlphaSorter(BSShaderProperty::RenderPass** apPassPtrOne, BSShaderProperty::RenderPass** apPassPtrTwo) {
	if ((*apPassPtrTwo)->pGeometry == (*apPassPtrOne)->pGeometry)
		return 0;

	NiBound* pBoundA = (*apPassPtrTwo)->pGeometry->m_kWorldBound;
	NiBound* pBoundB = (*apPassPtrOne)->pGeometry->m_kWorldBound;
	NiBound* pDefaultBound = NiBound::GetGlobalWorldBound();

	if (!pBoundA)
		pBoundA = pDefaultBound;

	if (!pBoundB)
		pBoundB = pDefaultBound;

	NiPoint3 kCameraDirection = (*(NiCamera**)0x11FFE38)->GetWorldDirection();
	float a = kCameraDirection.Dot(pBoundA->m_kCenter) - pBoundA->m_fRadius;
	float b = kCameraDirection.Dot(pBoundB->m_kCenter) - pBoundB->m_fRadius;

	if (FloatEqual(a,b)) {
		return 0;
	}
	else if (a <= b) {
		return -1;
	}
	else {
		return 1;
	}
}

// This one's cool.
// Game doesn't reset the render state, so objects *not* having alpha blending inherit the state from the one that did.
// Game also breaks if you use No_Fade flag in combination with NiAlphaController modifying fAlpha, causing it to flicker. (One disables alpha, and the other one sets it. Every frame.)
void __fastcall SetBlendAlpha(void* apThis, void*, NiPropertyState* shaderProps) {
	SetAlphaBlendEnable(0, 0);
	BSShaderProperty* shadeProp = shaderProps->GetShadeProperty<BSShaderProperty>();
	if (!shadeProp || shadeProp->m_eShaderType == -1) {
		return;
	}
	NiAlphaProperty* alphaProp = shaderProps->GetAlphaProperty();
	unsigned short flags = alphaProp ? alphaProp->m_usFlags.Get() : 0;
	bool bBlend = (flags & 1) != 0;
	bool bEnableBlend = ((shadeProp->fAlpha < 1.0f && !shadeProp->HasNoFade()) || shadeProp->fFadeAlpha < 1.0f || bBlend);
	if (bEnableBlend) {
#if _DEBUG
		_MESSAGE("[SetBlendAlpha] Current pass: %s, shader type: %s\n", BSShaderProperty::RenderPass::GetCurrentPassName(), shadeProp->GetShaderType());
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

bool NVSEPlugin_Load(NVSEInterface* nvse) {
	char iniDir[MAX_PATH];
	GetModuleFileNameA(GetModuleHandle(NULL), iniDir, MAX_PATH);
	strcpy((char*)(strrchr(iniDir, '\\') + 1), "Data\\NVSE\\Plugins\\FART.ini");
	bool bForceTMSAA = GetPrivateProfileInt("Main", "bForceTMSAA", 0, iniDir);
	bool bAlphaBlendFix = GetPrivateProfileInt("Main", "bAlphaBlendFix", 1, iniDir);
	bool bTexEffectFix = GetPrivateProfileInt("Main", "bTexEffectFix", 1, iniDir);
	bForcePatchParticles = GetPrivateProfileInt("Main", "bForcePatchParticles", 1, iniDir);
	bool bAlphaFlickerFix = GetPrivateProfileInt("Main", "bAlphaFlickerFix", 1, iniDir);

	if (!nvse->isEditor) {
		if (bAlphaBlendFix) {
			for (UInt32 callAddr : { 0x10AF378, 0x10AF7E0, 0x10AFA60, 0x10AFE98, 0x10B0040, 0x10B0218, 0x10B03B8, 0x10B0598, 0x10B0740, 0x10B08E0, 0x10B0A80, 0x10B0C18, 0x10B0DC0, 0x10B0F40, 0x10B10C0, 0x10B1240, 0x10B13C0, 0x10B1540, 0x10B16C0, 0x10B1878, 0x10B1A00, 0x10B1B88, 0x10B1D10, 0x10B1EA0, 0x10B2030, 0x10B21C0, 0x10B2388, 0x10B2510, 0x10B2690, 0x10B2828, 0x10B29A0, 0x10B2B18, 0x10B2C90, 0x10B2E30, 0x10B2FD0, 0x10B3160, 0x10B32E8, 0x10B3470, 0x10B3618, 0x10B3828, 0x10B39D8, 0x10B3B70, 0x10B3CF8, 0x10B3E98, 0x10B4028, 0x10B41B8, 0x10B4348, 0x10B44E0, 0x10B4680, 0x10B4820, 0x10B49B8, 0x10B4B50, 0x10B4CE8, 0x10B4E68, 0x10B5000, 0x10B51C0, 0x10B5340, 0x10B5500, 0x10B56C0, 0x10B5850, 0x10B59F8, 0x10B5B90, 0x10B5D38, 0x10B5F28, 0x10B60C8, 0x10B6270, 0x10B6418, 0x10B65C8, 0x10B6770, 0x10B6920, 0x10B6AC0, 0x10B6C58, 0x10B6E10, 0x10B6FB8, 0x10B7158, 0x10B72F8, 0x10B7498, 0x10B7618, 0x10B77A0, 0x10B7938, 0x10B7AD0, 0x10B7C70, 0x10B8A00, 0x10B8F00, 0x10B9210, 0x10B9B28, 0x10BA430, 0x10BAE18, 0x10BAFE0, 0x10BB490, 0x10BB608, 0x10BB828, 0x10BBA00, 0x10BBBD0, 0x10BBD88, 0x10BBF38, 0x10BC0F0, 0x10BC2E0, 0x10BC698, 0x10BC978 })
			{
				SafeWrite32(callAddr, UInt32(SetBlendAlpha));
			}
			WriteRelJump(0xBBC5FD, SetBlendAlpha);
			ReplaceCall(0xBC8F0B, SetBlendAlpha);
		}

		ReplaceCall(0xB9956C, (UInt32)CheckFlags);

		if (bTexEffectFix) {
			ReplaceVirtualFunc(0x10B7E54, RegisterPassGeometryGroup);
		}

		if (bForceTMSAA) {
			ReplaceCall(0x4DB187, (UInt32)SetShaderPackageHook);
			ReplaceCall(0x4DCB9D, (UInt32)SetShaderPackageHook);
		}

		if (bAlphaFlickerFix) {
			SafeWrite32(0xB99A29 + 1, (UInt32)AlphaSorter);
			SafeWrite32(0xB99A39 + 1, (UInt32)AlphaSorter);
			SafeWriteBuf(0xB63500, (void*)"\x6A\x01\x8B\x51\x08\x90\x90\x90", 8);
		}
	}
	else {
		bIsGeck = 1;
		if (bForceTMSAA) {
			ReplaceCall(0x429D5B, SetShaderPackageHook);
			ReplaceCall(0x53198B, SetShaderPackageHook);
		}
	}

	return true;
}