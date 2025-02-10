#pragma once
#include "../Graph/Graph/DirectedGraph.h"

//Создать Вершину
template <class TMark, class TMAttributes, class TRoad>
TMark* CreateMark(DirectedGraph<TMark, TRoad>& graph, TMAttributes attributes){
    return graph.AddVertex(TMark(attributes));;
}

template <class TMark, class TRoad>
TMark* CreateMark(DirectedGraph<TMark, TRoad>& graph,const TMark& mark){
    return graph.AddVertex(mark);
}

//Удаление Вершины
template <class TMark, class TMAttributes, class TRoad>
void RemoveMark(DirectedGraph<TMark, TRoad>& graph, TMAttributes attributes){
    if(!graph.RemoveVertex(TMark(attributes))) throw std::runtime_error("Вершины в графе нет");
}

//Удаление Вершины
template <class TMark, class TRoad>
void RemoveMark(DirectedGraph<TMark, TRoad>& graph,const TMark& mark){
    if(!graph.RemoveVertex(mark)) throw std::runtime_error("Вершины в графе нет");
}

//Соединить Вершины
template <class TMark, class TRoad, class TRAttributes>
bool ConnectMarks(DirectedGraph<TMark, TRoad>& graph, TMark* mark1, TMark* mark2, TRAttributes attributes){
    //Соединяем вершины в графе
    return(graph.AddEdge(*mark1, *mark2, TRoad(attributes)));
}

//Соединить Вершины
template <class TMark, class TRoad>
bool ConnectMarks(DirectedGraph<TMark, TRoad>& graph, TMark* mark1, TMark* mark2, TRoad road){
    //Соединяем вершины в графе
    return(graph.AddEdge(*mark1, *mark2, road));
}


//Удаление дороги
template <class TMark, class TRoad>
void DisconnectMarks(DirectedGraph<TMark, TRoad>& graph, TMark* mark1, TMark* mark2, TRoad road){
    if(!graph.RemoveEdge(*mark1, *mark2, road)) throw std::runtime_error("Вершин / ребра в графе нет");
}


