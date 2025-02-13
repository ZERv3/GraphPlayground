#pragma once

#include "LinkedList.hpp"
#include <ostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
    auto* current = list.GetNode(0); // Добавь метод GetHead() в LinkedList, если его нет
    os << "[ ";
    while (current) {
        os << current->data;
        if (current->next) os << " -> ";
        current = current->next;
    }
    os << " ]";
    return os;
}