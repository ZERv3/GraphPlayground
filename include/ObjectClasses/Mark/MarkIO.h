#pragma once

#include "Mark.h"
#include "ostream"
#include "sstream"

template <class TV, class TG>
std::ostream& operator<<(std::ostream& outStream, const Mark<TV, TG>& mark) {
    outStream << "<" << mark.GetType() << ">\n" << mark.GetValue();
    return outStream;
}


template <class TV, class TG>
std::istream& operator>>(std::istream& is, Mark<TV, TG>& mark) {
    char start, comma;
    TV value;
    TG group;

    //Читаем открывающую скобку (
    is >> start;
    if (start != '(') {
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> group; // Используем уже перегруженный оператор >>

    // Читаем запятую
    is >> comma;
    if (comma != ',') {
        is.setstate(std::ios::failbit);
        return is;
    }
    std::string temp;
    std::getline(is, temp, ')'); // Читаем строку
    std::stringstream ss(temp);
    ss >> value;
    // Создаём объект
    mark = Mark<TV, TG>(value, group);
    
    return is;
}



