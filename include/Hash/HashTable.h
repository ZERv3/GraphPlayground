#pragma once

#include "../Sequences/LinkedList.hpp"
#include "Functional.h"

template <typename TKey, typename TValue>
class HashTable;

//Шаблонный класс элемента хеш-таблицы
template <typename TKey, typename TValue>
class HT_Item {
    friend class HashTable<TKey, TValue>;
private:
    TKey key;
    TValue value;
public:
    //Конструктор элемента
    HT_Item(): key(TKey()), value(TValue()){};
    
    HT_Item(TKey key, TValue value): key(key), value(value){}; //Данные копируются в HT_Item
    
    //Получить ключ
    const TKey& GetKey() const {return this->key;}
    
    TKey* GetKeyPtr() {return &(this->key);} //Возвращает указатель на память с key
    
    //Получить значение
    TValue GetValue() const {return this->value;}
    
    //Возвращает ссылку на значение
    TValue& GetValue() {return this->value;}
    
    //Установить значение
    void SetValue(const TValue& newValue){ this->value = newValue;}
    
    //Проверка на заполняемость
    bool IsEmpty(){return (this->value == TValue());}
    
    bool operator==(const HT_Item<TKey, TValue>& other){
        return ((this->key == other.GetKey()) && (this->value == other.GetValue()));
    }
    
    
};

//Шаблонный класс хеш-таблицы
template <typename TKey, typename TValue>
class HashTable{
private:
    LinkedList<HT_Item<TKey, TValue>> items; //Объекты
    LinkedList<HT_Item<TKey, TValue>*>* data; //Массив цепочек указателей на объекты из items
    unsigned int capacity; //Емкость
    unsigned int fullness; //Заполненность
public:
    //Основной конструктор
    explicit HashTable(unsigned int capacity = 2):
        capacity(capacity),
        fullness(0),
        data(new LinkedList<HT_Item<TKey, TValue>*>[capacity]),
        items(LinkedList<HT_Item<TKey, TValue>>()){}
    
    [[nodiscard]] int GetCapacity() const {
        return this->capacity;
    }
    
    void Clear(){
        this->capacity = 0;
        this->fullness = 0;
        this->items.Clear();
        delete[] data;
    }
    
    [[nodiscard]] int GetFullness() const {
        return this->fullness;
    }
    
    LinkedList<HT_Item<TKey, TValue>*>* GetData() const {
        return this->data;
    }
    
    LinkedList<HT_Item<TKey, TValue>>& GetItems() {
        return this->items;
    }
    
    DynamicArray<TKey> GetKeys() const {
        DynamicArray<TKey> keys;
        
        auto current = this->items.GetNode(0);
            while (current != nullptr) {
                keys.PushBack(current->data.GetKey());
                current = current->next;
            }
        
        return keys;
    }
    
    TKey* GetKeyPtr(TKey key) const {
        int hKey = chf::hash(key, this->GetCapacity());
        auto current = this->data[hKey].GetNode(0);
        if(current != nullptr){
            while(current != nullptr){
                auto curKey = current->data->GetKey();
                if(curKey == key){
                    return current->data->GetKeyPtr();
                }
                else{
                    current = current->next;
                }
            }
        }
        return nullptr;
    }
    
    DynamicArray<TKey*> GetKeysPtrs() const {
        DynamicArray<TKey*> keys;
        
        auto current = this->items.GetNode(0);
        while (current != nullptr) {
            TKey* keyPtr = GetKeyPtr(current->GetData().GetKey());
//            std::cout << "\tKEY[" << keyPtr << "]:\n " << *keyPtr << "\n" << std::endl;
            keys.PushBack(keyPtr);
            current = current->next;
        }

        return keys;
    }
    
    
    //Добавление элемента в список
    HT_Item<TKey, TValue>* ItemsAdd(const TKey& key,const TValue& value){
//        std::cout << &key << std::endl;
        HT_Item<TKey, TValue> item(key, value);
//        std::cout << item.GetKeyPtr() << "\n";
        
        auto current = this->items.GetNode(0);
        if(current != nullptr){
            int i = 0;
            while(current != nullptr){
                auto curKey = current->data.GetKey();
                if(curKey == key){
                    current->data.SetValue(value);
                    return &(items.GetElement(i));
                }
                else{
                    current = current->next;
                    i++;
                }
            }
        }
        
        this->items.PushFront(item);
        return &(items.GetTail());
    }
    
    //Поисковик локального индекса (Рабочий)
    int FindKeyListIndex(const TKey& key) const {
        int hKey = chf::hash(key, this->GetCapacity());
        
        auto current = this->data[hKey].GetNode(0);
        
        if(current != nullptr){
            int i = 0;
            while(current != nullptr){
                auto curKey = current->data->GetKey();
                if(curKey == key){
                    return i;
                }
                else{
                    i++;
                    current = current->next;
                }
            }
        }
        return -1;
    }
    
    
    
    bool Contains(TKey key) const {
        return (FindKeyListIndex(key)!=-1);
    }
    
    
    
    TValue GetValue(TKey key) const {
        int index = FindKeyListIndex(key);
        if(index==-1){
            return TValue();
        }
        auto hKey = chf::hash(key, this->capacity);
        return (this->data[hKey].GetElement(index)->GetValue());
    }
    
    TValue& GetValue(TKey key) {
        if(!Contains(key)) {throw std::runtime_error(" Ключа в хэш-таблице нет");}
        int index = FindKeyListIndex(key);
        auto hKey = chf::hash(key, this->capacity);
        return (this->data[hKey].GetElement(index)->GetValue());
    }
    
    TKey* Insert(const TKey& key, const TValue& value) {
//        std::cout << &key << std::endl;
        auto* item = ItemsAdd(key, value); //Получили указатель на item
//        std::cout << item->GetKeyPtr() << std::endl;
        InsertInternal(item);
        return item->GetKeyPtr();
    }

    void Insert(HT_Item<TKey, TValue>* item) {
        InsertInternal(item);
    }

    // Внутренний метод для добавления элемента
    void InsertInternal(HT_Item<TKey, TValue>* item) {
        auto key = item->GetKey();
        int hKey = chf::hash(key, this->GetCapacity()); // Хэш-ключ (Индекс массива списков)
        auto& list = this->data[hKey]; // Ссылка на список по индексу
        bool itemEdited = false;

        auto current = list.GetNode(0);
        while (current != nullptr) {
            auto curKey = current->data->GetKey();
            if (curKey == key) {
                itemEdited = true; // Найден элемент с таким же ключом
                break;
            }
            current = current->next;
        }

        if (!itemEdited) {
            list.PushFront(item);
            this->fullness++;
        }
    }
    
    void Refill(){
        this->fullness = 0;
        int len = this->items.GetLength();
        if(len == 0) {}
        if(len == 1){
            auto current = this->items.GetElement(0);
            Insert(&current);
        }
        if(len > 1){
            auto current = this->items.GetNode(0);
            while(current != nullptr){
                Insert(&(current->data));
                current = current->next;
            }
        }
        
    }
    
    void AutoResize(double limitLoadFactor, int multiplier) {
        double loadFactor = static_cast<double>(GetFullness()) / static_cast<double>(GetCapacity());
        if(loadFactor > limitLoadFactor) {
//            std::cout << "Load Factor: " << loadFactor << "\n";
            
            //Удаляем старую хэш-таблицу
            delete[] this->data;
            
            //Расширенная пустая хэш-таблица
            this->data = new LinkedList<HT_Item<TKey, TValue>*>[capacity*multiplier];
            this->capacity*=multiplier;
            Refill();
        }
    }
    
    TKey* Add(const TKey& key,const TValue& value){
//        std::cout << &key << std::endl;
        AutoResize(0.75, 2);
        TKey* keyPtr = Insert(key, value);
        return keyPtr;
    }
    
    int FindKeyItemsIndex(TKey key){
        auto current = this->items.GetNode(0);
        
        if(current != nullptr){
            int i = 0;
            while(current != nullptr){
                auto curKey = current->data.GetKey();
                if(curKey == key){
                    return i;
                }
                else{
                    i++;
                    current = current->next;
                }
            }
        }
        return -1;
    }
    
    bool Remove(TKey key) {
        int hKey = chf::hash(key, this->GetCapacity());
        int index = (this->data[hKey]).GetLength() > 0 ? FindKeyListIndex(key) : -1;
        int itemsIndex = (this->items).GetLength() > 0 ? FindKeyItemsIndex(key) : -1;
        
        if (index != -1) {
            this->data[hKey].Remove(index);
            this->items.Remove(itemsIndex);
            this->fullness--;
            return true;
        }
        else{return false;}
    }
};
