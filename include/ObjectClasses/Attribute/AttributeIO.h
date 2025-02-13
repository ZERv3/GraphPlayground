#pragma once
#include "Attribute.h"

#include <sstream>

std::ostream& operator<<(std::ostream& outStream, const Attribute& attr) {
    
    int precision = 2;
    if (std::floor(attr.GetValue()) == attr.GetValue()) {
        precision = 0; // Целое число — без знаков после запятой
    } else if (std::floor(attr.GetValue() * 10) == attr.GetValue() * 10) {
        precision = 1; // Один знак после запятой
    }

    outStream << std::format("{:.{}f} {}", attr.GetValue(), precision, attr.GetSymbol());
    
    return outStream;
}

std::istream& operator>>(std::istream& is, Attribute& attr) {
    float newValue;
    is >> newValue;
    attr.SetValue(newValue);
    return is;
}
