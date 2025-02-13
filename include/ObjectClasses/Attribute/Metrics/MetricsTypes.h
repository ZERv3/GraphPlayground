#pragma once
#include "../Attribute.h"

// Базовый класс
class Metrics : public Attribute {
public:
    explicit Metrics(double value = 0.0) : Attribute(value) {}
    Metrics operator+(const Metrics& other) {return Metrics(value + other.value);}
    explicit Metrics(const Attribute& attr) {this->value = attr.GetValue();}
    static Metrics max() {
        return Metrics(Attribute::max());
    }
};

class Kilometre : public Metrics {
private:
    [[nodiscard]] const char* GetSymbol() const override { return "км"; }

public:
    explicit Kilometre(double value = 0.0) : Metrics(value) {}
    
    explicit Kilometre(const Metrics& attr) {this->value = attr.GetValue();}
    static Kilometre max() {
        return Kilometre(Metrics::max());
    }
};

class Metre : public Metrics {
private:
    [[nodiscard]] const char* GetSymbol() const override { return "м"; }

public:
    explicit Metre(double value = 0.0) : Metrics(value) {}
    
    explicit Metre(const Metrics& attr) {this->value = attr.GetValue();}
    static Metre max() {
        return Metre(Metrics::max());
    }
};
