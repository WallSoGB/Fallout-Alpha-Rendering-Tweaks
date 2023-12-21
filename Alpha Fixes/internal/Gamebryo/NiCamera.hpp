#pragma once

#include "NiAVObject.hpp"
#include "NiRect.hpp"
#include "NiFrustum.hpp"

NiSmartPointer(NiCamera);

class NiCamera : public NiAVObject {
public:
	NiCamera();
	virtual ~NiCamera();

	float			m_aafWorldToCam[4][4];
	NiFrustum		m_kViewFrustum;
	float			m_fMinNearPlaneDist;
	float			m_fMaxFarNearRatio;
	NiRect<float>	m_kPort;
	float			m_fLODAdjust;

	CREATE_OBJECT(NiCamera, 0xA71430);

	// 0x45BBE0
	const NiFrustum* GetFrustum() const { return &m_kViewFrustum; }

	const NiRect<float>* GetViewport() const { return &m_kPort; }

	// 0x712E60
	void SetViewport(const NiRect<float>& akPort) {
		m_kPort = akPort;
	}

	// 0x45BBA0
	__forceinline NiPoint3 GetWorldDirection() const {
		NiPoint3 result;
		m_kWorld.m_Rotate.GetCol(0, result);
		return result;
	}

	// 0x4E9C10
	__forceinline NiPoint3 GetWorldUpVector() const {
		NiPoint3 result;
		m_kWorld.m_Rotate.GetCol(1, result);
		return result;
	}

	// 0x4E9C50
	__forceinline NiPoint3 GetWorldRightVector() const {
		NiPoint3 result;
		m_kWorld.m_Rotate.GetCol(2, result);
		return result;
	}
};

ASSERT_SIZE(NiCamera, 0x114);