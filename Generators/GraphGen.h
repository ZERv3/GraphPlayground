#pragma once

#include <random>

#include "../Interface/GraphHandWrite.h"

//Генераторы 
#include "../ObjectClasses/Mark/MarkGen.h"
#include "../ObjectClasses/Road/RoadGen.h"

std::random_device rd;
std::mt19937 gen(rd());

template <typename TAttributes>
inline DirectedGraph<Mark<std::string, TransportGroup>, Road<TAttributes, TransportLine>> GenerateGraph (int vertexCount, int edgesCount){
    DirectedGraph<Mark<std::string, TransportGroup>, Road<TAttributes, TransportLine>> graph;
    
    for(int i = 0; i < vertexCount; i++) CreateMark(graph, GenerateRandomMark());
    
    int edgesAdded = 0;
    auto verts = graph.GetVerticesPtrs();
    
    while(edgesAdded != edgesCount) {
        int sourceIndex = std::uniform_int_distribution<>(0, vertexCount - 1)(gen);
        int destIndex = std::uniform_int_distribution<>(0, vertexCount - 1)(gen);
        while(destIndex == sourceIndex) destIndex = std::uniform_int_distribution<>(0, vertexCount - 1)(gen);
        
        bool newEdgeAdded = ConnectMarks(graph, verts.GetElement(sourceIndex), verts.GetElement(destIndex), GenerateRandomRoad<TAttributes>());
        if(newEdgeAdded){edgesAdded++;}
    }
    
    return graph;
}


