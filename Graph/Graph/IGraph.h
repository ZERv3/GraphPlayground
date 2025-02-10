#pragma once

#include "../../Hash/HashTable.h"
#include "../Edge/Edge.h"

//Абстрактный тип графа с реализацией добавления и удаления вершин
template <typename TVertex, typename TWeight>
class IGraph{
protected:
    HashTable<TVertex, HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>> >> adjacencyTable;
public:
    IGraph(){
        this->adjacencyTable = HashTable<TVertex, HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>> >>();
    }
    ~IGraph(){
        this->adjacencyTable = HashTable<TVertex, HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>> >>();
    }
    
    void Clear(){
        this->adjacencyTable = HashTable<TVertex, HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>> >>();
    }
    
    bool Contains(const TVertex& vertex) const {
        return adjacencyTable.Contains(vertex);
    }
    
    HashTable<TVertex, HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>> >>& GetAdjacencyTable() {
        return this->adjacencyTable;
    }
    
    DynamicArray<TVertex> GetVertices() const {
        return adjacencyTable.GetKeys();
    }
    
    TVertex* GetVertexPtr(TVertex vertex) const {
        return adjacencyTable.GetKeyPtr(vertex);
    }
    
    DynamicArray<TVertex*> GetVerticesPtrs() const {
//        std::cout << "ADJ_TABLE:\n" << adjacencyTable.GetKeysPtrs() << "\n";
        return adjacencyTable.GetKeysPtrs();
    }
    
    DynamicArray<TVertex*> GetNeighboursPtrs(const TVertex& vertex) const {
        if(!this->adjacencyTable.Contains(vertex)) throw std::runtime_error("Граф не хранит эту вершину");
        return adjacencyTable.GetValue(vertex).GetKeys();
    }
    
    DynamicArray<Edge<TVertex, TWeight>> GetVertexEdgesOut(const TVertex& vertex) const {
        if(this->adjacencyTable.Contains(vertex)){
            auto vertexHT = adjacencyTable.GetValue(vertex);
            
            //Распаковываем items из adjacencyTable
            LinkedList<HT_Item<TVertex*, DynamicArray<Edge<TVertex, TWeight>>>> items = vertexHT.GetItems();
            
            //Создаем пустой дин.массив для ребер
            DynamicArray<Edge<TVertex, TWeight>> edges;
            for (auto* it = items.ToBegin(); *it != *items.ToEnd(); ++(*it)) {
                // Разыменовываем итератор, чтобы получить DynamicArray<> из HT<TVertex*, DynamicArray<>>
                DynamicArray<Edge<TVertex, TWeight>> edgesPart = (**it).GetValue();
                
                //Здесь Concat с каждым дин.массивом из vertexHT
                if(edgesPart.GetLength() > 0){
                    edges.Concat(&edgesPart);
                }
            }
//            std::cout << "=-=-=-=-=-=-=-=\n";
//            for(int i = 0; i < edges.GetLength(); i++){
//                std::cout << edges.GetElement(i).GetEndVertex() << " | ";
//            }
//            std::cout << "\n=-=-=-=-=-=-=-=" << std::endl;
            return edges;
        }
        return DynamicArray<Edge<TVertex, TWeight>>();
    }
    
    DynamicArray<Edge<TVertex, TWeight>> GetEdges() const {
        DynamicArray<TVertex> vertices = GetVertices();
        DynamicArray<Edge<TVertex, TWeight>> edges;
        for (auto* it = vertices.ToBegin(); *it != *vertices.ToEnd(); ++(*it)) {
            auto edgesPart = GetVertexEdgesOut(**it);
            edges.Concat(&edgesPart);
        }
        return edges;
    }
    
    DynamicArray<Edge<TVertex, TWeight>>& GetEdges(const TVertex& source, TVertex* destination){
        if(adjacencyTable.Contains(source)&& adjacencyTable.Contains(*destination)){
            HashTable<TVertex*, DynamicArray<Edge<TVertex, TWeight>>> subHT = adjacencyTable.GetValue(source);
            return subHT.GetValue(destination);
        }
        throw std::runtime_error("Одна или обе вершины не были найдены в графе");
    }
    
     TVertex* AddVertex(const TVertex& vertex){
        TVertex* vertPtr = adjacencyTable.GetKeyPtr(vertex);
//         std::cout << "{" << vertPtr << "}\n";
         if(!vertPtr){ //Вершины не было в графе
             HashTable< TVertex*, DynamicArray<Edge<TVertex, TWeight>> > destinationTable;
             TVertex* ptr =adjacencyTable.Add(vertex, destinationTable);
//             std::cout << "{" << ptr << "}: " << ptr->GetValue() << std::endl;
             return ptr;
         }
         else return vertPtr; //Вершина уже есть в графе
    };
    
    bool RemoveVertex(TVertex vertex){
        if(!adjacencyTable.Contains(vertex)) return false;
        auto curItemNode = adjacencyTable.GetItems().GetNode(0); //LinkedList Node Pointer
        while(curItemNode != nullptr){
            if(!(curItemNode->GetData().GetKey() == vertex) && curItemNode->GetData().GetValue().Contains(&vertex)){
                curItemNode->GetData().GetValue().Remove(&vertex);
            }
            curItemNode = curItemNode->next;
        }
        adjacencyTable.Remove(vertex);
        return true;
    }
    
    virtual bool AddEdge(TVertex& source, TVertex& destination, TWeight& weight) = 0;
    virtual bool RemoveEdge(TVertex& source, TVertex& destination, TWeight& weight) = 0;
};

