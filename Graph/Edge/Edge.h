#pragma once

#include "../../Hash/Functional.h"

template <typename TVertex, typename TWeight>
class Edge{
private:
    
    //Убрать дублирование данных [+]
    //UPD: Вместо копирования данных, используются указатели на вершины
    TVertex* sourceVertex;
    TVertex* endVertex;
    TWeight weight; //Сделать более абстрактным [+]
    
public:
    Edge() :
        sourceVertex(nullptr),
        endVertex(nullptr),
        weight(TWeight()){}
    
    Edge(TVertex& sourceVertex,TVertex& endVertex,TWeight& weight){
            this->sourceVertex = &sourceVertex;
            this->endVertex = &endVertex;
            this->weight = weight;
        }
    
    ~Edge(){
        sourceVertex = nullptr;
        endVertex = nullptr;
        weight = TWeight();
    }
    
    TWeight GetWeight() const {
        return this->weight;
    }
    
    void SetWeight(TWeight& newWeight){
        weight = newWeight;
    }
    
    TVertex* GetSourceVertex() const {
        return this->sourceVertex;
    }
    
    TVertex* GetEndVertex() const {
        return this->endVertex;
    }
    
    bool operator==(const Edge<TVertex, TWeight>& other) const {
        if ((sourceVertex == nullptr) != (other.sourceVertex == nullptr) ||
            (endVertex == nullptr) != (other.endVertex == nullptr) ||
            (weight == TWeight()) != (other.weight == TWeight())) {
            return false;
        }
        
        return (!sourceVertex || *sourceVertex == *other.sourceVertex) &&
               (!endVertex || *endVertex == *other.endVertex) &&
               (weight == other.weight);
    }
};

namespace chf {
template <typename TV, typename TW>
inline bool isEqual(const Edge<TV, TW>& edge1, const Edge<TV, TW>& edge2)
{
    return
        (edge1.GetSourceVertex() && edge2.GetSourceVertex() ?
         isEqual(*(edge1.GetSourceVertex()), *(edge2.GetSourceVertex())) :
         edge1.GetSourceVertex() == edge2.GetSourceVertex()) &&

        (edge1.GetEndVertex() && edge2.GetEndVertex() ?
         isEqual(*(edge1.GetEndVertex()), *(edge2.GetEndVertex())) :
         edge1.GetEndVertex() == edge2.GetEndVertex()) &&

        (edge1.GetWeight() && edge2.GetWeight() ?
         isEqual(*(edge1.GetWeight()), *(edge2.GetWeight())) :
         edge1.GetWeight() == edge2.GetWeight());
}
}
