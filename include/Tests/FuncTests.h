#pragma once

#include <cassert>

#include "../Interface/GraphFileInterface.h"
#include "../Graph/Algorithms/Algorithms.h"


#include "../ObjectClasses/TransportIO.h" //Система обозначений дорог и метод
using namespace TransportMapper;

#include "../ObjectClasses/CTM.h"
#include "../ObjectClasses/CTMMap.h" //Система параметров (стоимость, время, расстояние)
using namespace AttributeMapper;

#include "../ObjectClasses/Mark/MarkIO.h" //Абстрактный тип меток (вершин графа)
#include "../ObjectClasses/Road/RoadIO.h" //Абстрактный тип дорог (ребер графа)

#include "../Generators/GraphGen.h"

template <typename TMark, typename TRoad, typename TAttributes>
class FunctionalTests {
public:
    static void FuncLoadFromFileTest(){
        for (int i = 1; i<7; i++) {
            DirectedGraph<TMark, TRoad> graph;
            HashTable<std::pair<std::string, std::string>, TMark*> vertices;
            GraphFileInterface<TMark, TRoad, TAttributes>::LoadGraphFromFile(graph, vertices, "../include/Tests/temps/test"+std::to_string(i)+".txt");
            assert(graph.GetVertices().GetLength() == 7+i);
        }
    }
    
    static void FuncCreateVertexTest(){
        DirectedGraph<TMark, TRoad> graph;
        for (int i = 0; i < 10; i++) {
            TMark mark = GenerateRandomMark();
            CreateMark(graph, mark);
        }
        assert(graph.GetVertices().GetLength() == 10);
    }
    
    static void FuncCreateEdgeTest(){
        DirectedGraph<TMark, TRoad> graph;
        for (int i = 0; i < 10; i++) {
            TMark mark = GenerateRandomMark();
            CreateMark(graph, mark);
        }
        
        auto verts = graph.GetVerticesPtrs();
        auto* mark1 = verts.GetElement(0);
        
        for (int i = 0; i < 10; i++){
            auto* mark2 = verts.GetElement(i);
            ConnectMarks(graph, mark1, mark2, GenerateRandomRoad<TAttributes>());
        }
        assert(graph.GetEdges().GetLength() == 10);
    }
    
    static void FuncDijkstraTest(){
        DirectedGraph<TMark, TRoad> graph;
        HashTable<std::pair<std::string, std::string>, TMark*> vertices;
        
        GraphFileInterface<TMark, TRoad, TAttributes>::LoadGraphFromFile(graph, vertices, "../include/Tests/temps/test1.txt");
        auto* mark1 = graph.GetVertexPtr(TMark("Экллипс", TransportGroup(TransportGroup::Types::SUBWAY)));
        auto* mark2 = graph.GetVertexPtr(TMark("Скай", TransportGroup(TransportGroup::Types::BUS)));
        
        auto path = Dijkstra<CompareByTime<TAttributes, TransportLine>>::template FindShortestPath<TMark, TRoad, TAttributes>(graph, *mark1, *mark2);
        assert(path.GetLength() == 5);
        
//        std::cout << path.GetLength();
    }
    
    static void FuncBFSTest(){
        DirectedGraph<TMark, TRoad> graph;
        HashTable<std::pair<std::string, std::string>, TMark*> vertices;
        
        GraphFileInterface<TMark, TRoad, TAttributes>::LoadGraphFromFile(graph, vertices, "../include/Tests/temps/test1.txt");
        auto* mark1 = graph.GetVertexPtr(TMark("Экллипс", TransportGroup(TransportGroup::Types::SUBWAY)));
        
        auto bfs = BFS::ComputeLevels(graph, *mark1);
        
        assert(bfs.GetKeys().GetLength() == 6);
        
//        std::cout << bfs.GetKeys().GetLength();
    }
    
    static void FuncDFSTest(){
        DirectedGraph<TMark, TRoad> graph;
        HashTable<std::pair<std::string, std::string>, TMark*> vertices;
        
        GraphFileInterface<TMark, TRoad, TAttributes>::LoadGraphFromFile(graph, vertices, "../include/Tests/temps/test1.txt");
        auto* mark1 = graph.GetVertexPtr(TMark("Экллипс", TransportGroup(TransportGroup::Types::SUBWAY)));
        
        auto neightbours = DFS::GetReachableNeighbours(graph, *mark1);
        
        assert(neightbours.GetLength() == 8);
        
//        std::cout << neightbours.GetLength();
    }
};
