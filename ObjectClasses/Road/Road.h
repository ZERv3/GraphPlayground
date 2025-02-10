#pragma once
template <typename TAttributes, typename RType>
class Road{
private:
    TAttributes attributes;
    RType type;
public:
    struct ComplexAttrs {
        TAttributes attris;
        RType type;
        ComplexAttrs(): attris(TAttributes()), type(RType()){}
        ComplexAttrs(TAttributes attris, RType type): attris(attris), type(type){}
    };
    
    Road():
        attributes(TAttributes()),
        type(RType()){}
    
    Road(TAttributes attributes, RType type): attributes(attributes),
        type(type){}
    
    Road(ComplexAttrs attr): attributes(attr.attris), type(attr.type){}
    
    Road(RType type): attributes(TAttributes()), type(type){}
    
    ~Road(){
        attributes = TAttributes();
        type = RType();
    }
    
    TAttributes GetAttributes() const {
        return attributes;
    }
    
    RType GetType() const {
        return type;
    }
    
    bool operator==(const Road<TAttributes, RType>& other) const {
        return type == other.GetType();
    }
    
    // Перегрузка оператора +, возвращающая новый объект Road,
        // в котором атрибуты и тип получены как сумма соответствующих полей.
    Road<TAttributes, RType> operator+(Road<TAttributes, RType>& other) {
        return Road<TAttributes, RType>(
            this->attributes + other.attributes,
            this->type);
    }
    
    static Road<TAttributes, RType> max(){
        return Road<TAttributes, RType>(
                                        TAttributes::max(),
                                        RType()
                                        );
    }
};

template <class TAttributes, class RType>
class CompareByTime {
public:
    bool operator()(const Road<TAttributes, RType>& road1,
                    const Road<TAttributes, RType>& road2) const {
        return road1.GetAttributes().GetTime() > road2.GetAttributes().GetTime();
    }
};

template <class TAttributes, class RType>
class CompareByMetrics {
public:
    bool operator()(const Road<TAttributes, RType>& road1,
                    const Road<TAttributes, RType>& road2) const {
        return road1.GetAttributes().GetDistance() > road2.GetAttributes().GetDistance();
    }
};

template <class TAttributes, class RType>
class CompareByCost {
public:
    bool operator()(const Road<TAttributes, RType>& road1,
                    const Road<TAttributes, RType>& road2) const {
        return road1.GetAttributes().GetCost() > road2.GetAttributes().GetCost();
    }
};
