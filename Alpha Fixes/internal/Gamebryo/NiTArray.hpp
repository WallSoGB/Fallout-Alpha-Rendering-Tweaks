#pragma once

#include "NiMemObject.hpp"

class NiTMallocInterface;
class NiTNewInterface;

template <class T_Data, class Allocator>
class NiTArray : public NiMemObject {
public:
	NiTArray(UInt32 uiMaxSize = 0, UInt32 uiGrowBy = 1) {
		m_usMaxSize = (UInt16)uiMaxSize;
		m_usGrowBy = (UInt16)uiGrowBy;
		m_usSize = 0;
		m_usESize = 0;

		if (m_usMaxSize > 0)
			m_pBase = Allocator::Allocate(m_usMaxSize);
		else
			m_pBase = 0;
	}

	virtual ~NiTArray();

	T_Data* m_pBase;
	UInt16 m_usMaxSize;
	UInt16 m_usSize;
	UInt16 m_usESize;
	UInt16 m_usGrowBy;
};

template <class T_Data> 
class NiTObjectArray : public NiTArray<T_Data, NiTNewInterface> {
public:
	NiTObjectArray(UInt32 uiMaxSize = 0, UInt32 uiGrowBy = 1) : NiTArray<T_Data, NiTNewInterface>(uiMaxSize, uiGrowBy) {};
};

template <class T_Data> 
class NiTPrimitiveArray : public NiTArray<T_Data, NiTMallocInterface> {
public:
	NiTPrimitiveArray(UInt32 uiMaxSize = 0, UInt32 uiGrowBy = 1) : NiTArray<T_Data, NiTMallocInterface>(uiMaxSize, uiGrowBy) {};
};

ASSERT_SIZE(NiTObjectArray<void*>, 0x10);
ASSERT_SIZE(NiTPrimitiveArray<void*>, 0x10);

typedef NiTPrimitiveArray<const char*> NiViewerStringsArray;