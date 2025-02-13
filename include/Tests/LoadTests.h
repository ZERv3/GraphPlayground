#pragma once

#include "../Generators/GraphGen.h"
#include "../Graph/Algorithms/Algorithms.h"

#include <chrono>
#include <cmath>

template<typename TVertex, typename TWeight, typename TAttributes>
class LoadTests{
public:
    static double LoadCreationTest(int vertexCount, int edgesCount) {
        using Clock = std::chrono::high_resolution_clock;

        auto start = Clock::now();
        auto graph = GenerateGraph<TAttributes>(vertexCount, edgesCount);
        auto end = Clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    static double LoadGetVerticesTest(int vertexCount, int edgesCount) {
        using Clock = std::chrono::high_resolution_clock;
        
        auto graph = GenerateGraph<TAttributes>(vertexCount, edgesCount);
        auto start = Clock::now();
        auto list = graph.GetVerticesPtrs();
        auto end = Clock::now();
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    static double LoadGetEdgesTest(int vertexCount, int edgesCount){
        using Clock = std::chrono::high_resolution_clock;
        
        auto graph = GenerateGraph<TAttributes>(vertexCount, edgesCount);
        auto start = Clock::now();
        auto list = graph.GetEdges();
        auto end = Clock::now();
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    //Нагрузочный тест алгоритма Дийкстры
    static double LoadDijkstraTest(int vertexCount, int edgesCount) {
        using Clock = std::chrono::high_resolution_clock;
                
        auto graph = GenerateGraph<TAttributes>(vertexCount, edgesCount); //Генерируем граф
        auto verts = graph.GetVerticesPtrs(); //Берем указатели на все вершины
        //Ищем вершины, максимально отдаленные друг от друга
            //С помощью BFS получаем для каждой вершины набор ее уровней кратчайшей достижимости
            //Сравниваем все наборы и берем максимальный по количеству уровней
            //Берем соответствующую вершину и одну из вершин на последнем уровне BFS для нее
        //Считаем Дийкстру для этих вершин
        
        TVertex* source = verts.GetElement(0);
        
        auto bfsDistsStart = BFS::ComputeLevels(graph, *source);
        int maxFullness = bfsDistsStart.GetFullness();

        for (int i = 1; i < verts.GetLength(); i++) {
            TVertex* vi = verts.GetElement(i);
            auto bfsDistsi = BFS::ComputeLevels(graph, *vi);
            int currentFullness =bfsDistsi.GetFullness();
            if(currentFullness > maxFullness){
                maxFullness = currentFullness;
                source = vi;
            }
        }
        auto bfsDistsEnd = BFS::ComputeLevels(graph, *source);
        
        auto* dest = bfsDistsEnd.GetValue(maxFullness-1).GetElement(0); //Просто берем первый из списка вершин на самом дальнем уровне
        
        auto start = Clock::now();

        Dijkstra<CompareByCost<TAttributes, TransportLine>> ::template FindShortestPath<TVertex, TWeight, TAttributes>(graph, *source, *dest);

        Dijkstra<CompareByTime<TAttributes, TransportLine>> ::template FindShortestPath<TVertex, TWeight, TAttributes>(graph, *source, *dest);

        Dijkstra<CompareByMetrics<TAttributes, TransportLine>> ::template FindShortestPath<TVertex, TWeight, TAttributes>(graph, *source, *dest);

        auto end = Clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        return duration/3;
    }
    
    static double LoadBFSTest(int vertexCount, int edgesCount) {
        using Clock = std::chrono::high_resolution_clock;
                
        auto graph = GenerateGraph<TAttributes>(vertexCount, edgesCount); //Генерируем граф
        auto verts = graph.GetVerticesPtrs();
        
        TVertex* source = verts.GetElement(0);
        
        auto bfsDistsStart = BFS::ComputeLevels(graph, *source);
        int maxFullness = bfsDistsStart.GetFullness();

        for (int i = 1; i < verts.GetLength(); i++) {
            TVertex* vi = verts.GetElement(i);
            auto bfsDistsi = BFS::ComputeLevels(graph, *vi);
            int currentFullness =bfsDistsi.GetFullness();
            if(currentFullness > maxFullness){
                maxFullness = currentFullness;
                source = vi;
            }
        }
        auto start = Clock::now();
        
        BFS::ComputeLevels(graph, *source);
        
        auto end = Clock::now();
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    
    static double LoadDFSTest(int vertexCount, int edgesCount){
        using Clock = std::chrono::high_resolution_clock;
                
        auto graph = GenerateGraph<TAttributes>(vertexCount, edgesCount); //Генерируем граф
        auto verts = graph.GetVerticesPtrs();
        
        TVertex* source = verts.GetElement(0);
        
        auto start = Clock::now();
        
        DFS::GetReachableNeighbours(graph, *source);
        
        auto end = Clock::now();
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    static void LoadAlgorithmsTests(int vertexCount, int edgesCount, double& dijkstraTime, double& bfsTime, double& dfsTime){
        using Clock = std::chrono::high_resolution_clock;
                
        auto graph = GenerateGraph<TAttributes>(vertexCount, edgesCount); //Генерируем граф
        auto verts = graph.GetVerticesPtrs();
        
        TVertex* source = verts.GetElement(0);
        
        auto bfsDistsStart = BFS::ComputeLevels(graph, *source);
        int maxFullness = bfsDistsStart.GetFullness();

        for (int i = 1; i < verts.GetLength(); i++) {
            TVertex* vi = verts.GetElement(i);
            auto bfsDistsi = BFS::ComputeLevels(graph, *vi);
            int currentFullness =bfsDistsi.GetFullness();
            if(currentFullness > maxFullness){
                maxFullness = currentFullness;
                source = vi;
            }
        }
        
        auto bfsDistsEnd = BFS::ComputeLevels(graph, *source);
        auto* dest = bfsDistsEnd.GetValue(maxFullness-1).GetElement(0); //Просто берем первый из списка вершин на самом дальнем уровне
        
        auto start = Clock::now();
        Dijkstra<CompareByCost<TAttributes, TransportLine>> ::template FindShortestPath<TVertex, TWeight, TAttributes>(graph, *source, *dest);

        Dijkstra<CompareByTime<TAttributes, TransportLine>> ::template FindShortestPath<TVertex, TWeight, TAttributes>(graph, *source, *dest);

        Dijkstra<CompareByMetrics<TAttributes, TransportLine>> ::template FindShortestPath<TVertex, TWeight, TAttributes>(graph, *source, *dest);
        auto end = Clock::now();
        dijkstraTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        
        start = Clock::now();
        BFS::ComputeLevels(graph, *source);
        end = Clock::now();
        bfsTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        start = Clock::now();
        DFS::GetReachableNeighbours(graph, *source);
        end = Clock::now();
        dfsTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
};


