#pragma once

#include <format>
#include <cmath>

// Базовый класс
class Attribute {
protected:
    float value;
    
public:
    virtual const char* GetSymbol() const { return "?"; }
    
    Attribute(float value = 0.0) : value(value) {}
    
    virtual ~Attribute() = default;

    virtual std::string GetFormatted() const {
        int precision = 2;
        if (std::floor(value) == value) {
            precision = 0; // Целое число — без знаков после запятой
        } else if (std::floor(value * 10) == value * 10) {
            precision = 1; // Один знак после запятой
        }

        return std::format("{:.{}f} {}", value, precision, GetSymbol());
    }

    float GetValue() const { return value; }
    void SetValue(float newValue) {value = newValue;}

    // Операторы сравнения (общие для всех атрибутов)
    bool operator==(const Attribute& other) const { return value == other.value; }
    bool operator!=(const Attribute& other) const { return !(*this == other); }
    bool operator<(const Attribute& other) const { return value < other.value; }
    bool operator>(const Attribute& other) const { return value > other.value; }
    bool operator<=(const Attribute& other) const { return value <= other.value; }
    bool operator>=(const Attribute& other) const { return value >= other.value; }
    Attribute operator+(const Attribute& other) const {return Attribute(value+other.value);}
    
    static Attribute max(){
        return Attribute(std::numeric_limits<double>::max());
    }
};
