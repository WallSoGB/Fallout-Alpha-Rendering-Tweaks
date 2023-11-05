#pragma once

typedef void* NiTMapIterator;

template <class T_Key, class T_Data> class NiTMapItem {
public:
    NiTMapItem* m_pkNext;
    T_Key       m_key;
    T_Data      m_val;
};

template <class Allocator, class T_Key, class T_Data> class NiTMapBase {
public:
    typedef NiTMapItem<T_Key, T_Data> Entry;

    NiTMapBase(UInt32 uiHashSize = 37) {
        m_uiHashSize = uiHashSize;
        m_uiCount = 0;

        UInt32 uiSize = sizeof(NiTMapItem<T_Key, T_Data>*) * m_uiHashSize;
        m_ppkHashTable = (NiTMapItem<T_Key, T_Data>**)NiAlloc(uiSize);
        memset(m_ppkHashTable, 0, m_uiHashSize * sizeof(NiTMapItem<T_Key, T_Data>*));
    };
    virtual                             ~NiTMapBase();
    virtual UInt32                      KeyToHashIndex(T_Key key);
    virtual bool                        IsKeysEqual(T_Key key1, T_Key key2);
    virtual void                        SetValue(NiTMapItem<T_Key, T_Data>* pkItem, T_Key key, T_Data data);
    virtual void                        ClearValue(NiTMapItem<T_Key, T_Data>* pkItem);
    virtual NiTMapItem<T_Key, T_Data>*  NewItem();
    virtual void                        DeleteItem(NiTMapItem<T_Key, T_Data>* pkItem);

    UInt32                      m_uiHashSize;
    NiTMapItem<T_Key, T_Data>** m_ppkHashTable;
    UInt32                      m_uiCount;

    UInt32 GetCount() const { return m_uiCount; }

    // 0x853130
    bool GetAt(T_Key key, T_Data& dataOut) {
        UInt32 hashIndex = KeyToHashIndex(key);
        NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[hashIndex];
        while (item) {
            if (IsKeysEqual(item->m_key, key)) {
                dataOut = item->m_val;
                return true;
            }
            item = item->m_pkNext;
        }
        return false;
    }

    // 0x844700
    void SetAt(T_Key key, T_Data data) {
        UInt32 hashIndex = KeyToHashIndex(key);
        NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[hashIndex];
        while (item) {
            if (IsKeysEqual(item->m_key, key)) {
                item->m_val = data;
                return;
            }
            item = item->m_pkNext;
        }
        NiTMapItem<T_Key, T_Data>* nuEntry = NewItem();
        SetValue(nuEntry, key, data);
        nuEntry->m_pkNext = m_ppkHashTable[hashIndex];
        m_ppkHashTable[hashIndex] = nuEntry;
        m_uiCount++;
    }
};