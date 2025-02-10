#pragma once

#include "Edge.h"
#include <ostream>

template <typename TV, typename TW>
std::ostream& operator<<(std::ostream& outStream, const Edge<TV, TW>& edge){
    outStream
    << "EDGE : ("
    << *(edge.GetSourceVertex()) << " -> "
    << *(edge.GetEndVertex()) << " , "
    << edge.GetWeight()
    << ")";
    return outStream;
}


