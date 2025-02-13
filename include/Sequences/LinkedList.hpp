#pragma once

#include "Sequence.h"
#include "DynamicArray.hpp"

template <class T>
class LinkedList : public Sequence<T> {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(T data, Node* next = nullptr) : data(data), next(next) {}
        T& GetData() {return this->data;}
    };

    Node* head;
    Node* tail;
    int length;

public:
    class LinkedListIterator : public Sequence<T>::Iterator {
    private:
        Node* current;

    public:
        explicit LinkedListIterator(Node* start) : current(start) {}

        bool operator==(const typename Sequence<T>::Iterator& other) const override {
            const auto* otherIterator = dynamic_cast<const LinkedListIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename Sequence<T>::Iterator& other) const override {
            return !(*this == other);
        }

        T& operator*() override {
            return current->data;
        }

        typename Sequence<T>::Iterator& operator++() override {
            if (current) {
                current = current->next;
            }
            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() override {
        return new LinkedListIterator(head);
    }

    typename Sequence<T>::Iterator* ToEnd() override {
        return new LinkedListIterator(nullptr);
    }
   
    T& GetHead() override {
        return head->data;
    }

    T& GetTail() override {
        return tail->data;
    }

    T& GetElement(int index) override {
        return GetNode(index)->data;
    }

    Node* GetNode(int index) const {
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }
    
    int FindIndex(T value){
        Node* current = head;
        for (int i = 0; i < this->length; ++i) {
            if(current->data == value){return i;}
            else current=current->next;
        }
        return -1;
    }
    
    int FindIndex(T* value){
        Node* current = head;
        for (int i = 0; i < this->length; ++i) {
            if(*(current->data) == *(value)){return i;}
            else current=current->next;
        }
        return -1;
    }
    
    bool Find(T value){
        return FindIndex(value)!=-1;
    }

    void Swap(T& a, T& b) override {
        T temp = a;
        a = b;
        b = temp;
    }

    void Set(T item, int index) override {
        GetNode(index)->data = item;
    }
    
    void Remove(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }

        Node* toDelete = nullptr;

        if (index == 0) { // Удаление головы
            toDelete = head;
            head = head->next;
            if (length == 1) { // Если список состоял из одного элемента
                tail = nullptr;
            }
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            toDelete = current->next;
            current->next = toDelete->next;

            if (toDelete == tail) { // Если удаляется хвост
                tail = current;
            }
        }

        delete toDelete;
        length--;
    }

    LinkedList<T>* GetSubsequence(int startIndex, int endIndex) override {
        if (endIndex >= length) {
            endIndex = length - 1;
        }
        auto* sublist = new LinkedList<T>();
        Node* current = head;
        for (int i = 0; i <= endIndex; ++i) {
            if (i >= startIndex) {
                sublist->PushFront(current->data);
            }
            current = current->next;
        }
        return sublist;
    }

    [[nodiscard]] int GetLength() const override {
        return length;
    }

    [[nodiscard]] bool IsEmpty() const {
        return length == 0;
    }
    
    ~LinkedList() {
        if(!IsEmpty()) Clear();
    }

    void PushFront(T item) override {
        Node* newNode = new Node(item);
        if (length == 0) {
            head = tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void PushBack(T item) override {
        Node* newNode = new Node(item, head);
        if (length == 0) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

    void Insert(T item, int index) override {
        if (index == 0) {
            PushBack(item);
        } else if (index == length) {
            PushFront(item);
        } else {
            Node* current = GetNode(index - 1);
            Node* newNode = new Node(item, current->next);
            current->next = newNode;
            length++;
        }
    }

    void Concat(Sequence<T>* list) override {
        for (int i = 0; i < list->GetLength(); ++i) {
            LinkedList<T>::PushFront(list->GetElement(i));
        }
    }

    void Clear() override{
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        length = 0;
    }

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0) {
        for (int i = 0; i < count; ++i) {
            LinkedList<T>::PushFront(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), length(0) {
        Node* current = list.head;
        while (current != nullptr) {
            LinkedList<T>::PushFront(current->data);
            current = current->next;
        }
    }

    explicit LinkedList(const DynamicArray<T>& dynamicArray) : head(nullptr), tail(nullptr), length(0) {
        for (int i = 0; i < dynamicArray.GetLength(); ++i) {
            LinkedList<T>::PushFront(dynamicArray.GetElement(i));
        }
    }
};
