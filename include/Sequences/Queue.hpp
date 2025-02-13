#pragma once

#include "LinkedList.hpp"
#include <stdexcept>

template <class T>
class Queue : public LinkedList<T> {
public:
    // Добавляет элемент в очередь
    void Enqueue(T item) {
        // В реализации LinkedList метод PushFront добавляет элемент в хвост списка.
        this->PushFront(item);
    }

    // Извлекает и возвращает первый элемент очереди
    T Dequeue() {
        if (this->GetLength() == 0) {
            throw std::out_of_range("Queue is empty");
        }
        // Сохраняем первый элемент, затем удаляем его из списка
        T front = this->GetHead();
        this->Remove(0);
        return front;
    }

    // Возвращает ссылку на первый элемент очереди без удаления
    T& Peek() {
        if (this->GetLength() == 0) {
            throw std::out_of_range("Queue is empty");
        }
        return this->GetHead();
    }
};
