#pragma once
#include "../Attribute.h"

// Базовый класс
class Currency : public Attribute {
    
public:
    Currency(float value = 0.0) : Attribute(value) {}
    Currency operator+(const Currency& other) const {return Currency(value+other.value);}
    Currency(Attribute attr) {this->value = attr.GetValue();}
    static Currency max() {
        return Currency(Attribute::max());
    }
};

// Подкласс для RUB (₽ справа)
class RUB : public Currency {
private:
    const char* GetSymbol() const override {return "₽";}

public:
    RUB(float value = 0.0) : Currency(value) {}
    RUB(Currency cur) : Currency(cur) {}
    
    std::string GetFormatted() const override{
        return std::format("{:.2f} {}", value, GetSymbol()); // 2 знака после запятой
    }
    static RUB max() {
        return RUB(Currency::max());
    }
};

// Подкласс для USD ($ слева)
class USD : public Currency {
private:
    const char* GetSymbol() const override {return "$";}
    
public:
    USD(float value = 0.0) : Currency(value) {}
    USD(Currency cur) : Currency(cur) {}
    
    std::string GetFormatted() const override{
        return std::format("{} {:.2f}", GetSymbol(), value); // 2 знака после запятой
    }
    
    USD(Attribute attr) {this->value = attr.GetValue();}
    static USD max() {
        return USD(Currency::max());
    }
    
};
