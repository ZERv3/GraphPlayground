#pragma once

#include "DynamicArray.h"
#include <stdexcept>
#include <functional>
//#include <utility>

// Шаблонный класс BinaryHeap реализует двоичную кучу (min-heap) с возможностью передачи компаратора Compare.
template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
private:
    // Используем твой DynamicArray для хранения элементов кучи.
    DynamicArray<T> data;
    Compare cmp;

    // Функция siftUp – поднимает элемент вверх, пока не восстановится свойство кучи.
    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            // Если текущий элемент имеет более высокий приоритет (меньше для min-heap),
            // меняем его местами с родительским.
            if (cmp(data.GetElement(index), data.GetElement(parent))) {
                std::swap(data[index], data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Функция siftDown – опускает элемент вниз, чтобы восстановить свойство кучи.
    void siftDown(int index) {
        int n = data.GetSize();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int target = index; // Индекс наименьшего элемента (для min-heap)

            if (left < n && cmp(data[left], data[target])) {
                target = left;
            }
            if (right < n && cmp(data[right], data[target])) {
                target = right;
            }

            // Если обнаружена позиция, в которой текущий элемент не соответствует правилу кучи,
            // меняем его с наименьшим из потомков.
            if (target != index) {
                std::swap(data[index], data[target]);
                index = target;
            } else {
                break;
            }
        }
    }

public:
    BinaryHeap() = default;

    // Вставка нового элемента в кучу.
    void push(const T& item) {
        // Добавляем элемент в конец динамического массива.
        data.Insert(item, data.GetSize());
        // Производим просеивание вверх, чтобы восстановить свойство кучи.
        int index = data.GetSize() - 1;
        siftUp(index);
    }

    // Удаляет и возвращает элемент с наивысшим приоритетом (минимальный элемент для min-heap).
    T pop() {
        if (data.GetSize() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        T topItem = data[0];
        // Перемещаем последний элемент в корень.
        data[0] = data[data.GetSize() - 1];
        // Удаляем последний элемент.
        data.Remove(data.GetSize() - 1);
        // Если куча не пуста, просеиваем корень вниз для восстановления свойства кучи.
        if (data.GetSize() > 0) {
            siftDown(0);
        }
        return topItem;
    }

    // Возвращает элемент с наивысшим приоритетом без удаления.
    const T& top() const {
        if (data.GetSize() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return data.GetElement(0);
    }

    // Возвращает количество элементов в куче.
    int size() const {
        return data.GetSize();
    }

    // Проверяет, пуста ли куча.
    bool empty() const {
        return data.GetSize() == 0;
    }
};
