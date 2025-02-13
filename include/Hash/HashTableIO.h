#pragma once

#include "HashTable.h"

#include "../Sequences/LinkedListIO.hpp"
#include <ostream>

template <typename TKey, typename TValue>
std::ostream& operator<<(std::ostream& outStream, const HT_Item<TKey, TValue>& item) {
    outStream << "["
    << item.GetKey()
    << " , "
    << item.GetValue()
    << "]";
    return outStream;
}

template <typename TKey, typename TValue>
std::ostream& operator<<(std::ostream& outStream, const HashTable<TKey, TValue>& HT) {
    outStream << "HASHTABLE:" << std::endl;
    auto HTData = HT.GetData();
    for (int i = 0; i < HT.GetCapacity(); i++) {
        auto list = HTData[i];
        outStream << "\t" << list << std::endl;
    }
    return outStream;
}
