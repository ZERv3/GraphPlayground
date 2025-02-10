#pragma once
#include "../Attribute.h"

// Базовый класс
class Time : public Attribute {
public:
    Time(float value = 0.0) : Attribute(value) {}
    Time operator+(const Time& other) {return Time(value + other.value);}
    Time(Attribute attr){this->value = attr.GetValue();}
    static Time max(){
        return Time(Attribute::max());
    }
};

class Hour : public Time {
private:
    const char* GetSymbol() const override { return "ч"; }

public:
    Hour(float value = 0.0) : Time(value) {}
    Hour(Time time){this->value = time.GetValue();}
    static Hour max(){
        return Hour(Time::max());
    }
};

class Minute : public Time {
private:
    const char* GetSymbol() const override { return "мин"; }

public:
    Minute(float value = 0.0) : Time(value) {}
    Minute(Time time){this->value = time.GetValue();}
    static Minute max(){
        return Minute(Time::max());
    }
};
