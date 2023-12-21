#pragma once

#include "NiPoint3.hpp"
#include "BSMemObject.hpp"

class NiCamera;

class NiBound : public BSMemObject {
public:
	NiBound() : m_kCenter(NiPoint3(0.0f,0.0f,0.0f)) , m_fRadius(0.0f) {};
	~NiBound() {};

	NiPoint3	m_kCenter;
	float		m_fRadius;

	static NiBound	ms_kDefaultBound;

	static NiBound* GetGlobalWorldBound();
};

ASSERT_SIZE(NiBound, 0x010);