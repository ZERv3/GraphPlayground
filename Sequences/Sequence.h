#pragma once

template <class T>
class Sequence {
public:
    virtual void Insert(T item, int index) = 0;
    virtual void Concat(Sequence<T>* list) = 0;
    virtual void Clear() = 0;
    virtual T& GetHead() = 0;
    virtual T& GetTail() = 0;
    virtual T& GetElement(int index) = 0;
    virtual void Swap(T& a, T& b) = 0;
    virtual void Set(T item, int index) = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
    virtual int GetLength() const = 0;
    virtual void PushFront(T item) = 0;
    virtual void PushBack(T item) = 0;
    virtual ~Sequence() = default;

    class Iterator {
    public:
        virtual ~Iterator() = default;
        virtual Iterator& operator++() = 0;
        virtual bool operator==(const Iterator& other) const = 0;
        virtual bool operator!=(const Iterator& other) const = 0;
        virtual T& operator*() = 0;
    };

    virtual Iterator* ToBegin() = 0;
    virtual Iterator* ToEnd() = 0;
};
