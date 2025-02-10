#pragma once
#include "../Attribute.h"

// Базовый класс
class Metrics : public Attribute {
public:
    Metrics(float value = 0.0) : Attribute(value) {}
    Metrics operator+(const Metrics& other) {return Metrics(value + other.value);}
    Metrics(Attribute attr) {this->value = attr.GetValue();}
    static Metrics max() {
        return Metrics(Attribute::max());
    }
};

class Kilometre : public Metrics {
private:
    const char* GetSymbol() const override { return "км"; }

public:
    Kilometre(double value = 0.0) : Metrics(value) {}
    
    Kilometre(Metrics attr) {this->value = attr.GetValue();}
    static Kilometre max() {
        return Kilometre(Metrics::max());
    }
};

class Metre : public Metrics {
private:
    const char* GetSymbol() const override { return "м"; }

public:
    Metre(double value = 0.0) : Metrics(value) {}
    
    Metre(Metrics attr) {this->value = attr.GetValue();}
    static Metre max() {
        return Metre(Metrics::max());
    }
};
