#pragma once

#include "NiObjectNET.hpp"
#include "NiProperty.hpp"
#include "NiTPointerList.hpp"
#include "NiTransform.hpp"
#include "NiUpdateData.hpp"

class NiCullingProcess;
class NiNode;
class NiCamera;
class NiDX9Renderer;
class NiBound;

NiSmartPointer(bhkNiCollisionObject);
NiSmartPointer(NiAVObject);

class NiAVObject : public NiObjectNET {
public:
	NiAVObject();
	virtual ~NiAVObject();

	virtual void			UpdateControllers(NiUpdateData* arData);
	virtual void			ApplyTransform();
	virtual void			Unk_39();
	virtual NiAVObject*		GetObject_(const NiFixedString& kName);
	virtual NiAVObject*		GetObjectByName(const NiFixedString& kName);
	virtual void			SetSelectiveUpdateFlags(bool* bSelectiveUpdate, bool bSelectiveUpdateTransforms, bool* bRigid);
	virtual void			UpdateDownwardPass(const NiUpdateData& arData, UInt32 uFlags);
	virtual void			UpdateSelectedDownwardPass(const NiUpdateData& arData, UInt32 uFlags);
	virtual void			UpdateRigidDownwardPass(const NiUpdateData& arData, UInt32 uFlags);
	virtual void			Unk_46(void* arg);
	virtual void			UpdateTransform();
	virtual void			UpdateWorldData(const NiUpdateData& arData);
	virtual void			UpdateWorldBound();
	virtual void			UpdateTransformAndBounds(const NiUpdateData& arData);
	virtual void			PreAttachUpdate(NiNode* pEventualParent, const NiUpdateData& arData);
	virtual void			PreAttachUpdateProperties(NiNode* pEventualParent);
	virtual void			DetachParent();
	virtual void			UpdateUpwardPassParent(void* arg);
	virtual void			OnVisible(NiCullingProcess* kCuller);
	virtual void			PurgeRendererData(NiDX9Renderer* pkRenderer);

	enum NiFlags : UInt32
	{
		APP_CULLED = 0x1,
		SELECTIVE_UPDATE= 0x2,
		SELECTIVE_UPDATE_TRANSFORMS = 0x4,
		SELECTIVE_UPDATE_CONTROLLER = 0x8,
		SELECTIVE_UPDATE_RIGID = 0x10,
		DISPLAY_OBJECT = 0x20,
		DISABLE_SORTING = 0x40,
		SELECTIVE_UPDATE_TRANSFORMS_OVERRIDE = 0x80,
		IS_NODE = 0x100,
		SAVE_EXTERNAL_GEOM_DATA = 0x200,
		NO_DECALS = 0x400,
		ALWAYS_DRAW = 0x800,
		ACTOR_NODE = 0x1000,
		FIXED_BOUND = 0x2000,
		TOP_FADE_NODE = 0x4000,
		IGNORE_FADE = 0x8000,
		NO_ANIM_SYNC_X = 0x10000,
		NO_ANIM_SYNC_Y = 0x20000,
		NO_ANIM_SYNC_Z = 0x40000,
		NO_ANIM_SYNC_S = 0x80000,
		ACTOR_CULLED = 0x100000,
		NO_DISMEMBER_VALIDITY = 0x200000,
		RENDER_USE = 0x400000,
		MATERIALS_APPLIED = 0x800000,
		HIGH_DETAIL = 0x1000000,
		FORCE_UPDATE = 0x2000000,
		PREPROCESSED_NODE = 0x4000000,
		UNK_27 = 0x8000000,
		UNK_28 = 0x10000000,
		IS_POINTLIGHT = 0x20000000,
		DONE_INIT_LIGHTS = 0x40000000,
		IS_INSERTED = 0x80000000,
	};

	NiNode*							m_pkParent;
	bhkNiCollisionObjectPtr			m_spCollisionObject;
	NiBound*						m_kWorldBound;
	NiTPointerList<NiPropertyPtr>	m_kPropertyList;
	Bitfield32						m_uiFlags;
	NiTransform						m_kLocal;
	NiTransform						m_kWorld;
};

ASSERT_SIZE(NiAVObject, 0x9C);