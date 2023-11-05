#pragma once

#include "NiSmartPointer.hpp"

NiSmartPointer(NiFixedString);

class NiFixedString {
public:
	NiFixedString();
	NiFixedString(const char* pcString);
	NiFixedString(const NiFixedString& kString);
	~NiFixedString();

	const char* m_kHandle;
};

ASSERT_SIZE(NiFixedString, 0x4)