#pragma once
#include "../Attribute.h"

// Базовый класс
class Currency : public Attribute {
    
public:
    explicit Currency(double value = 0.0) : Attribute(value) {}
    Currency operator+(const Currency& other) const {return Currency(value+other.value);}
    explicit Currency(const Attribute& attr) {this->value = attr.GetValue();}
    static Currency max() {
        return Currency(Attribute::max());
    }
};

// Подкласс для RUB (₽ справа)
class RUB : public Currency {
private:
    [[nodiscard]] const char* GetSymbol() const override {return "₽";}

public:
    explicit RUB(float value = 0.0) : Currency(value) {}
    explicit RUB(Currency cur) : Currency(cur) {}
    
    [[nodiscard]] std::string GetFormatted() const override{
        return std::format("{:.2f} {}", value, GetSymbol()); // 2 знака после запятой
    }
    static RUB max() {
        return RUB(Currency::max());
    }
};

// Подкласс для USD ($ слева)
class USD : public Currency {
private:
    [[nodiscard]] const char* GetSymbol() const override {return "$";}
    
public:
    explicit USD(float value = 0.0) : Currency(value) {}
    explicit USD(Currency cur) : Currency(cur) {}
    
    [[nodiscard]] std::string GetFormatted() const override{
        return std::format("{} {:.2f}", GetSymbol(), value); // 2 знака после запятой
    }

    [[maybe_unused]] USD(const Attribute& attr) {this->value = attr.GetValue();}
    static USD max() {
        return USD(Currency::max());
    }
    
};
