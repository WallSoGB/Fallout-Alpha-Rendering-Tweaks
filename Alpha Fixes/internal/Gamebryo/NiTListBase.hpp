#pragma once

#include "NiMemObject.hpp"

typedef void* NiTListIterator;

template <class T_Data>
class NiTListItem : public NiMemObject {
public:
	NiTListItem* m_pkNext;
	NiTListItem* m_pkPrev;
	T_Data m_element;
};

template <class Allocator, class T_Data>
class  NiTListBase : public NiMemObject {
public:
    NiTListBase() : m_pkHead(0), m_pkTail(0), m_uiCount(0) {};
    ~NiTListBase() {};

    NiTListItem<T_Data>* m_pkHead;
    NiTListItem<T_Data>* m_pkTail;
    UInt32 m_uiCount;
};