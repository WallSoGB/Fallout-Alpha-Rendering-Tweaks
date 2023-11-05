#pragma once

#include "BSMemObject.hpp"


template <class T_Data>
class BSSimpleList : public BSMemObject {
public:
	BSSimpleList() : m_item(0), m_pkNext(0) { }
	BSSimpleList(T_Data& item) : m_item(item), m_pkNext(0) {}
	~BSSimpleList() { 
		while (m_pkNext) {
			auto pNewNext = m_pkNext->m_pkNext;
			m_pkNext->m_pkNext = nullptr;
			if (m_pkNext)
				m_pkNext->~BSSimpleList();
			m_pkNext = pNewNext;
		}
		m_item = 0;
	}

	T_Data					m_item;
	BSSimpleList<T_Data>*	m_pkNext;
};

ASSERT_SIZE(BSSimpleList<UInt32>, 0x8);