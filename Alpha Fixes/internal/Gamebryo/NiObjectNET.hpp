#pragma once

#include "NiObject.hpp"
#include "NiFixedString.hpp"

class NiTimeController;
class NiExtraData;

class NiObjectNET : public NiObject {
public:
	NiObjectNET();
	virtual ~NiObjectNET();

	enum CopyType {
		COPY_NONE = 0x0,
		COPY_EXACT = 0x1,
		COPY_UNIQUE = 0x2,
	};

	NiFixedString					m_kName;
	NiPointer<NiTimeController>		m_spControllers;
	NiExtraData**					m_ppkExtra;
	UInt16							m_usExtraDataSize;
	UInt16							m_usMaxSize;

	const char* GetName() const { return m_kName.m_kHandle; };
};

ASSERT_SIZE(NiObjectNET, 0x18);