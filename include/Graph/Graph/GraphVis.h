#pragma once

#include "DirectedGraph.h"
#include "../Edge/EdgeIO.h"
#include "../../Hash/HashTableIO.h"

#include <string>
#include <fstream>
#include <sstream>

template <typename TV, typename TW>
std::string GraphToDot(const DirectedGraph<TV, TW>& graph){
    std::stringstream dot;
    dot << "digraph G {\n";
    dot << "    // Graph visualization generated by Graphviz\n";
    
    // Генерация вершин
    auto vertices = graph.GetVertices();
    DynamicArray<TV*> verts = graph.GetVerticesPtrs();
    
    int size = vertices.GetLength();
    for (int i = 0; i < size; i++) {
        dot << "    " << i << " [label=\"" << vertices.GetElement(i) << "\", shape=component];\n";
    }
    
    
    // Получение рёбер из вершины
    DynamicArray<Edge<TV,TW>> edges = graph.GetEdges();
    for (int i = 0; i < edges.GetLength() ; i++) {    // edge - пара (destination, weight)
        auto edge = edges.GetElement(i);
        dot << "    " << vertices.Index(*(edge.GetSourceVertex()))
        << " -> " << vertices.Index(*(edge.GetEndVertex()))
        << " [label=\"" << edge.GetWeight()
        << "\", len=1.0, fontsize=\"10pt\"];\n";
    }
    
    // Завершение графа
    dot << "}\n";

    return dot.str();
}

template <typename TV, typename TW>
std::string GraphToDot(const DirectedGraph<TV, TW>& graph, const DynamicArray<Edge<TV, TW>>& path){
    std::stringstream dot;
    dot << "digraph G {\n";
    dot << "    // Graph visualization generated by Graphviz\n";
    
    HashTable<TV*, bool> pathVertHT;
    HashTable<Edge<TV, TW>, bool> pathEdgeHT;
    
    //Получение отмеченных вершин и ребер
    auto edgesArray = path.GetData();
    for (int i = 0; i < path.GetLength(); i++) {
        Edge<TV, TW> edge = edgesArray[i];
        auto svPtr = edge.GetSourceVertex();
        auto evPtr = edge.GetEndVertex();
        pathVertHT.Add(svPtr, true);
        pathVertHT.Add(evPtr, true);
        pathEdgeHT.Add(edge, true);
    }
    
    // Генерация вершин
    DynamicArray<TV> vertices = graph.GetVertices();
    DynamicArray<TV*> verts = graph.GetVerticesPtrs();
//    std::cout << "VERTS : " << verts << "\n" "\n";
    
    int size = vertices.GetLength();
    
    for (int i = 0; i < size; i++) {
        auto v = verts.GetElement(i);
        
        dot << "    " << i << " [shape=box, label=\"" << *v << "\"";
        if (pathVertHT.Contains(v)){
            dot << ", color=red, fontcolor=red";
        }
        dot << "];\n";
        
//        std::cout << "    " << i << " [label=\"" << vertices.GetElement(i) << "\"];" << "\n";
    }
    
    
    // Получение рёбер из вершины
    DynamicArray<Edge<TV,TW>> edges = graph.GetEdges();
//    std::cout << edges << std::endl;
    for (int i = 0; i < edges.GetLength() ; i++) {    // edge - пара (destination, weight)
        auto edge = edges.GetElement(i);
        auto w = edge.GetWeight();
        dot << "    " << vertices.Index(*(edge.GetSourceVertex()))
        << " -> " << vertices.Index(*(edge.GetEndVertex()))
        << " [label=\"" << w
        << "\", fontsize=\"10pt\"";
        if(pathEdgeHT.Contains(edge)) dot << ", color=red, fontcolor=red";
        dot << "];\n";
    }
    
    // Завершение графа
    dot << "}\n";

    return dot.str();
}
//=================================================================
template <class TV, class TW>
void SaveGraphVisualFile(const DirectedGraph<TV, TW>& graph, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    file << GraphToDot(graph);
    file.close();
}
template <class TV, class TW>
void SaveGraphVisualFile(const DirectedGraph<TV, TW>& graph,
                         const std::string& filename ,
                         const DynamicArray<Edge<TV, TW>>& path) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    file << GraphToDot(graph, path);
    file.close();
}
//=================================================================

template <class TV, class TW>
void RenderGraph(const DirectedGraph<TV, TW>& graph,
                 const std::string& filename,
                 const std::string& format = "png") {
    SaveGraphVisualFile(graph, filename + ".dot");

    std::string command = "dot -T" + format + " " + filename + ".dot" + " > " + filename + "." + format;
//        std::string command = "dot -Tpng graph.dot > out.png";
    int result = system(command.c_str());

    if (result != 0) {
        throw std::runtime_error("Failed to render graph. Ensure Graphviz is installed.");
    }
}

template <class TV, class TW>
void RenderGraph(const DirectedGraph<TV, TW>& graph,
                 const std::string& filename,
                 const DynamicArray<Edge<TV, TW>>& path,
                 const std::string& format = "png"){
    SaveGraphVisualFile(graph, filename + ".dot", path);

    std::string command = "dot -T" + format + " " + filename + ".dot" + " > " + filename + "." + format;
//        std::string command = "dot -Tpng graph.dot > out.png";
    int result = system(command.c_str());

    if (result != 0) {
        throw std::runtime_error("Failed to render graph. Ensure Graphviz is installed.");
    }
}
