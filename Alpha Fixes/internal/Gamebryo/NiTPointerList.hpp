#pragma once

#include "NiTPointerListBase.hpp"

class NiTPointerAllocator;

template <class T_Data>
class NiTPointerList : public NiTPointerListBase <NiTPointerAllocator, T_Data> {
};

ASSERT_SIZE(NiTPointerList<void*>, 0xC);