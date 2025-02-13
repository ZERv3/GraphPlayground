#pragma once
#include "../Attribute.h"

// Базовый класс
class Time : public Attribute {
public:
    explicit Time(double value = 0.0) : Attribute(value) {}
    Time operator+(const Time& other) {return Time(value + other.value);}
    explicit Time(const Attribute& attr){this->value = attr.GetValue();}
    static Time max(){
        return Time(Attribute::max());
    }
};

class Hour : public Time {
private:
    [[nodiscard]] const char* GetSymbol() const override { return "ч"; }

public:
    explicit Hour(double value = 0.0) : Time(value) {}
    explicit Hour(const Time& time){this->value = time.GetValue();}
    static Hour max(){
        return Hour(Time::max());
    }
};

class Minute : public Time {
private:
    [[nodiscard]] const char* GetSymbol() const override { return "мин"; }

public:
    explicit Minute(double value = 0.0) : Time(value) {}
    explicit Minute(const Time& time){this->value = time.GetValue();}
    static Minute max(){
        return Minute(Time::max());
    }
};
