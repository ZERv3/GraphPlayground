#pragma once

#include "Road.h"
#include "RoadAttributes.h"
#include "ostream"
#include "sstream"

template <typename TC, typename TM, typename TT>
std::ostream& operator<<(std::ostream& outStream, const RoadAttributes<TC, TM, TT>& roadAttr){
    TM distance = roadAttr.GetDistance();
    TT time = roadAttr.GetTime();
    TC cost = roadAttr.GetCost();
    outStream << distance << " | ";
    outStream << time;
    if(cost != TC()) outStream << "\n" << cost;
    return outStream;
}

template <typename TA, typename RT>
std::ostream& operator<<(std::ostream& outStream, const Road<TA, RT>& road){
    outStream << "["
    << road.GetType() << "]\n"
    << road.GetAttributes() << "";
    return outStream;
}

template <typename TC, typename TM, typename TT>
std::istream& operator>>(std::istream& is, RoadAttributes<TC, TM, TT>& attr) {
    TC newCost;
    TM newDistance;
    TT newTime;
    char comma;

    if (is >> newCost >> comma >> newDistance >> comma >> newTime) {
        attr.SetCost(newCost);
        attr.SetDistance(newDistance);
        attr.SetTime(newTime);
    } else {
        is.setstate(std::ios::failbit);  // Ошибка ввода
    }

    return is;
}

template <typename TA, typename RT>
std::istream& operator>>(std::istream& is, Road<TA, RT>& road) {
    char start, end, comma;
    RT type;
    TA attributes;

    // Читаем открывающую скобку '('
    is >> start;
    if (start != '(') {
        is.setstate(std::ios::failbit);
        return is;
    }

    // Читаем тип дороги
    is >> type;

    // Читаем запятую ','
    is >> comma;
    if (comma != ',') {
        is.setstate(std::ios::failbit);
        return is;
    }

    // Читаем атрибуты дороги
    is >> attributes;

    // Читаем закрывающую скобку ')'
    is >> end;
    if (end != ')') {
        is.setstate(std::ios::failbit);
        return is;
    }

    // Если всё корректно, создаём объект Road
    road = Road<TA, RT>(attributes, type);
    return is;
}


