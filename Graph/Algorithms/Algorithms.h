#pragma once

#include "../Graph/DirectedGraph.h" // Граф
#include "../../Sequences/PriorityQueue.h" // Приоритетная очередь для Дийкстры
#include "../../Sequences/Queue.h" // Обычная очередь для BFS

#include <limits>
#include <stdexcept>

// Шаблонный класс для поиска кратчайшего пути алгоритмом Дейкстры
template<typename Comparator>
class Dijkstra {
public:
    template <typename TVertex, typename TWeight, typename TAttributes>
    static DynamicArray<Edge<TVertex, TWeight>> FindShortestPath(const DirectedGraph<TVertex, TWeight>& graph, const TVertex& source, const TVertex& dest){
        HashTable<TVertex, TWeight> distances; //Реестр кратчайших растояния до вершин
        HashTable<TVertex, Edge<TVertex, TWeight>> prevEdges; //Реестр предыдущих вершины по кратчайшему пути
        DynamicArray<TVertex> verts = graph.GetVertices(); //Вершины
        
        for (int i = 0; i < verts.GetSize(); i++) {
            distances.Add(verts.GetElement(i), TWeight::max());
        }
        distances.Add(source, TWeight());
        
        struct Node {
            TVertex vertex;
            TWeight distance;
            bool operator>(const Node& other) const {
                Comparator cmp;
                return cmp(distance, other.distance);
            }
            void Print() const {
                std::cout << "" << vertex << "\n\t" << distance << "\n";
            }
        };
        
        PriorityQueue<Node, std::greater<Node>> pq; //Создали очередь пар вершина - расстояние
        
        pq.Enqueue({ source, TWeight() }); //Добавили в очередь источник
        
        while(!pq.IsEmpty()){
            Node currentNode = pq.Dequeue(); //Забрали из очереди пару вершину-расстояние
            
            //Попали в конечную точку?
            if (currentNode.vertex == dest) {
                break;
            }
            
            //Расстояние до взятой точки больше, чем в реестре кратчайших расстояний?
            if (Comparator()(currentNode.distance, distances.GetValue(currentNode.vertex))) {
                continue;
            }
            
            //Получаем все исходящие из вершины ребра
            DynamicArray<Edge<TVertex, TWeight>> edges = graph.GetVertexEdgesOut(currentNode.vertex);

            //Пробегаем по исходящим ребрам
            for (int i = 0; i < edges.GetSize(); i++) {
                Edge<TVertex, TWeight> edge = edges.GetElement(i);
                
                TVertex* neighbor = edge.GetEndVertex(); //Получаем соседа
                TWeight weight = edge.GetWeight(); //Получаем вес ребра
                TWeight newDist = currentNode.distance + weight; //Получаем расстояние до соседа
                
                //Если новое расстояние меньше, чем реестре расстояний
                if (!Comparator()(newDist, distances.GetValue(*neighbor))) {
                    distances.Add(*neighbor, newDist); //Перезаписали кратчайшее расстояние до соседа
                    prevEdges.Add(*neighbor, edge); //Перезаписали пред-ребро до соседа
                    pq.Enqueue({ *neighbor, newDist }); //Добавили соседа как новую вершину рассмотра
                }
            }
        }
        
        //Если остался бесконечно-большой вес
        if (distances.GetValue(dest).GetAttributes() == TAttributes::max()) {
            throw std::runtime_error("Путь не найден");
        }
        
        //Восстанавливаем путь
        DynamicArray<Edge<TVertex, TWeight>> path;
        TVertex current = dest;
        while (current != source) {
            Edge<TVertex, TWeight> edge = prevEdges.GetValue(current);
            path.PushBack(edge);
            current = *(edge.GetSourceVertex());
        }
        
        DynamicArray<Edge<TVertex, TWeight>> shortestPath(path.GetSize());
        for (int i = path.GetSize() - 1, j = 0; i >= 0; i--, j++) {
            shortestPath.Set(path.GetElement(i), j);
        }

        return shortestPath;
    }
};

class BFS {
public:
    template <typename TVertex, typename TWeight>
    static HashTable<int, DynamicArray<TVertex*>> ComputeLevels(const DirectedGraph<TVertex, TWeight>& graph,const TVertex& source) {
        
        if(!graph.Contains(source)) throw std::runtime_error("Source vertex not found in graph");
        TVertex* sourcePtr = graph.GetVertexPtr(source);
        
        HashTable<TVertex*, int> vertexLevels;
        DynamicArray<TVertex*> vertices = graph.GetVerticesPtrs();
        
        for (int i = 0; i < vertices.GetSize(); i++) {
            vertexLevels.Add(vertices.GetElement(i), -1);
        }
                
        vertexLevels.Add(sourcePtr, 0);
        
        HashTable<int, DynamicArray<TVertex*>> levelGroups;
        DynamicArray<TVertex*> group0; group0.PushBack(sourcePtr);
        levelGroups.Add(0, group0);
        
        Queue<TVertex*> queue;
        queue.Enqueue(sourcePtr);
        
        while (!queue.IsEmpty()) {
            TVertex* current = queue.Dequeue();
            int currentLevel = vertexLevels.GetValue(current);
            
            DynamicArray<Edge<TVertex, TWeight>> edges = graph.GetVertexEdgesOut(*current);
            for (int i = 0; i < edges.GetSize(); i++) {
                Edge<TVertex, TWeight> edge = edges.GetElement(i);
                TVertex* neighbor = edge.GetEndVertex();
                
                if (!vertexLevels.Contains(neighbor) || vertexLevels.GetValue(neighbor) == -1) {
                    int neighborLevel = currentLevel + 1;
                    vertexLevels.Add(neighbor, neighborLevel);
                    
                    if (!levelGroups.Contains(neighborLevel)) {
                        levelGroups.Add(neighborLevel, DynamicArray<TVertex*>());
                    }
                    
                    levelGroups.GetValue(neighborLevel).PushBack(neighbor);
                    queue.Enqueue(neighbor);
                }
            }
        }
        
        return levelGroups;
    }
};

class DFS {
private:
    template <typename TVertex, typename TWeight>
    static DynamicArray<TVertex*> GetReachesRecursive(const DirectedGraph<TVertex, TWeight>& graph, TVertex* sourcePtr, HashTable<TVertex*, bool>& visited){
        if(visited.Contains(sourcePtr)) return DynamicArray<TVertex*>();
        
        visited.Add(sourcePtr, true);
        
        DynamicArray<TVertex*> reaches;
        reaches.PushBack(sourcePtr);
        
        auto neighbours = graph.GetNeighboursPtrs(*sourcePtr);
        if(neighbours.IsEmpty()) return reaches;
        for(int i = 0; i < neighbours.GetLength(); i++){
            auto* v = neighbours.GetElement(i);
            auto rs = GetReachesRecursive(graph, v, visited);
            reaches.Concat(&rs);
        }
        return reaches;
    }
public:
    template <typename TVertex, typename TWeight>
    static DynamicArray<TVertex*> GetReachableNeighbours(const DirectedGraph<TVertex, TWeight>& graph, const TVertex& source){
        if(!graph.Contains(source)) throw std::runtime_error("Source vertex not found in graph");
        TVertex* sourcePtr = graph.GetVertexPtr(source);
        HashTable<TVertex*, bool> visited;
        return GetReachesRecursive(graph, sourcePtr, visited);
    }
};
