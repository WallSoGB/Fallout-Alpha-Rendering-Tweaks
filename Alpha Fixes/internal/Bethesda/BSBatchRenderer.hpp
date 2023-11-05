#pragma once

#include "NiTMap.hpp"
#include "BSSimpleList.hpp"
#include "NiTPointerList.hpp"
#include "BSShaderProperty.hpp"

class PersistentPassList {
	UInt32 filler[5];
};

class BSShader;
class NiTexture;

// BSSimpleArray<BSBatchRenderer::PassGroup, 1024> - PS3, FO3

class BSBatchRenderer : public NiObject {
public:
	virtual void RegisterPassGeometryGroup(BSShaderProperty::RenderPass* apRenderPass, UInt32 auiPassEnum);
	virtual void Unk_24(BSShaderManager::RenderPassType aeMinPass, BSShaderManager::RenderPassType aeMaxPass, bool abBlendAlpha);

	struct GeometryGroup;

	struct AccumStruct4 {
		PersistentPassList	kPassLists[5];
		UInt32				uiCount;

		void AddHead(UInt32 auiList, BSShaderProperty::RenderPass* apRenderPass);
		void AddTail(UInt32 auiList, BSShaderProperty::RenderPass* apRenderPass);
	};

	enum GroupTypes : SInt32 {
		GROUP_NONE = -1,
		GROUP_UNK_0 = 0,
		GROUP_UNK_1 = 1,
		GROUP_BLENDED_DECAL_SINGLE = 2,
		GROUP_BLENDED_DECAL_MULTI = 3,
		GROUP_UNK_4 = 4,
		GROUP_UNK_5 = 5,
		GROUP_REFRACT = 6,
		GROUP_UNK_7 = 7,
		GROUP_REFRACT_CLEAR = 8,
		GROUP_UNK_9 = 9,
		GROUP_UNK_10 = 10,
		GROUP_DEPTH_WORLD = 11,
		GROUP_DEPTH_PLAYER = 12,
	};

	enum TransparencyType : UInt32 {
		ALPHA_NONE = 0,
		ALPHA_STENCIL = 1,
		ALPHA_TEST_STENCIL = 2,
		ALPHA_TEST_NO_STENCIL = 3,
		ALPHA_NO_TMSAA = 4,
		ALPHA_MAX = 5,
	};

	AccumStruct4*									pAccumStructures4;
	NiTMap<BSShaderManager::RenderPassType, UInt32>	kPassMap; // PassType -> AccumStruct4 index
	DWORD											uiMaxPass;
	BSShaderManager::RenderPassType					ePassStart;
	BSShaderManager::RenderPassType					ePassEnd;
	DWORD*											pTextureBlendStagesList;
	BSSimpleList<UInt16>							kCurrentBatch;
	UInt32											uiGroupingAlphasGroupCount;
	bool											bAutoClearPasses;
	BSBatchRenderer::GeometryGroup*					pGeometryGroups[13];
	BSBatchRenderer::GeometryGroup*					pUngroupedAlphas[2];
	NiTPointerList<BSBatchRenderer::GeometryGroup*> kGroupingAlphasGroup[2];
	BSBatchRenderer::GeometryGroup*					pGroupedAlphas[2]; // 0 is for facegen stuff? FaceGenAccessory and FaceGenHairHat go there
};
ASSERT_SIZE(BSBatchRenderer, 0x98);