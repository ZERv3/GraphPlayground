#pragma once

#include <string>

namespace chf{
    inline int hash(const int index, int capacity){
        return index%capacity;
    }

    //Int Hash Function
    inline int hash(const int* index, int capacity){
        return (*index)%capacity;
    }

    //String Hash Function
    inline int hash(const std::string& word, int capacity){
        return (word.size())%capacity;
    }

    //String Pointer Hash Function
    inline int hash(const std::string* word, int capacity){
        return ((*word).size())%capacity;
    }

    template <class T>
    inline int hash(const T& mark, int capacity){
        return (sizeof(mark))%capacity;
    }
}
