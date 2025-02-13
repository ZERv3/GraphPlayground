#pragma once

#include "IGraph.h"

template <typename TVertex, typename TWeight>
class DirectedGraph : public IGraph<TVertex, TWeight>{
public:
    DirectedGraph() : IGraph<TVertex, TWeight>() {}
    bool AddEdge(TVertex& source, TVertex& destination, TWeight& weight) override {
        if(this->adjacencyTable.Contains(source) && this->adjacencyTable.Contains(destination)){
            // Получаем ссылку на хеш-таблицу, хранящую ребра из source
            HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>>>& destinationTable = this->adjacencyTable.GetValue(source);

            // Создаем ребро
            Edge<TVertex, TWeight> edge(source, destination, weight);
//            std::cout << "[" << edge.GetEndVertex() << "]: " << edge.GetEndVertex()->GetValue()  << std::endl;

            
            // Работаем с существующими ребрами
            if(destinationTable.Contains(&destination)){
                // Получаем ссылку на динамический массив ребер
                DynamicArray<Edge<TVertex, TWeight>>& edgesDynArray = destinationTable.GetValue(&destination);

                int index = edgesDynArray.Index(edge);// Ищем индекс ребра с такими же параметрами
                
                if(index != -1) {edgesDynArray.Set(edge, index); return false;} // Обновляем существующее ребро
                else edgesDynArray.PushBack(edge); // Добавляем новое ребро
                return true;
            }
            else{
                // Если раньше не было ребер к destination, создаем новый массив
                DynamicArray<Edge<TVertex, TWeight>> edgesDynArray;
                edgesDynArray.PushBack(edge);
                destinationTable.Add(&destination, edgesDynArray);
                return true; // Успешное добавление ребра
            }
            
        }
        throw std::runtime_error("Вершин(ы) в графе нет"); // Если одна из вершин отсутствует
    }
    
    bool RemoveEdge(TVertex& source, TVertex& destination, TWeight& weight) override {
        if(this->adjacencyTable.Contains(source) && this->adjacencyTable.Contains(destination)){
            // Получаем ссылку на хеш-таблицу, хранящую ребра из source
            HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>>>& destinationTable = this->adjacencyTable.GetValue(source);

            // Создаем ребро
            Edge<TVertex, TWeight> edgeToDel(source, destination, weight);
            
            // Работаем с существующими ребрами
            if(destinationTable.Contains(&destination)){
                // Получаем ссылку на динамический массив ребер
                DynamicArray<Edge<TVertex, TWeight>>& edgesDynArray = destinationTable.GetValue(&destination);

                int index = edgesDynArray.Index(edgeToDel);// Ищем индекс ребра с такими же параметрами

                if(index != -1) {edgesDynArray.Remove(index); return true;} // Удаляем найденное ребро
                else return false; //Ребра с таким типом не было
            }
            else return false; //Раньше к destination вершине не подводились ребра
        }
        return false; // Если одна из вершин отсутствует
    }
    
   
    
};
