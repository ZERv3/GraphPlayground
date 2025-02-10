#pragma once

#include <string>

namespace chf{
    inline int hash(const int index, unsigned int capacity){
        return index%capacity;
    }

    //Int Hash Function
    inline int hash(const int* index, unsigned int capacity){
        return (*index)%capacity;
    }

    //String Hash Function
    inline int hash(const std::string& word, unsigned int capacity){
        return (word.size())%capacity;
    }

    //String Pointer Hash Function
    inline int hash(const std::string* word, unsigned int capacity){
        return ((*word).size())%capacity;
    }

    template <class T>
    inline int hash(const T& mark, unsigned int capacity){
        return (sizeof(mark))%capacity;
    }
}
