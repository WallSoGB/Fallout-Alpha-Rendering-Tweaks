#pragma once

#include "NiTMapBase.hpp"

class NiTDefaultAllocator;

template <class T_Key, class T_Data>
class NiTMap : public NiTMapBase<NiTDefaultAllocator, T_Key, T_Data> {
public:
    NiTMap(UInt32 uiHashSize = 37) : NiTMapBase<NiTDefaultAllocator, T_Key, T_Data>(uiHashSize) {};
	~NiTMap() {};
};

static_assert(sizeof(NiTMap<UInt32, UInt32>) == 0x10, "Wrong structure size!");