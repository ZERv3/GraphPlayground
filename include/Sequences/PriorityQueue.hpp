#pragma once

#include "BinaryHeap.hpp"

template <class T, class Compare = std::less<T>>
class PriorityQueue {
private:
    BinaryHeap<T, Compare> heap; // Используем BinaryHeap вместо LinkedList

public:
    // Добавляет элемент в приоритетную очередь
    void Enqueue(const T& item) {
        heap.push(item);
    }

    // Удаляет и возвращает элемент с наивысшим приоритетом
    T Dequeue() {
        return heap.pop();
    }

    // Возвращает ссылку на элемент с наивысшим приоритетом без удаления
    const T& Peek() const {
        return heap.top();
    }

    // Проверяет, пуста ли очередь
    [[nodiscard]] bool IsEmpty() const {
        return heap.empty();
    }

    // Возвращает размер очереди
    [[nodiscard]] int GetSize() const {
        return heap.size();
    }
};
