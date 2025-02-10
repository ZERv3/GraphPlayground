#pragma once

template <class TValue, class TGroup>
class Mark {
private:
    TValue value;
    TGroup type;
public:
    struct ComplexAttrs {
        TValue value;
        TGroup group;
        ComplexAttrs(): value(TValue()), group(TGroup()){}
        ComplexAttrs(TValue value, TGroup group): value(value), group(group){}
    };
    Mark(TValue value = TValue(), TGroup type = TGroup()): value(value), type(type){}
    
    Mark(ComplexAttrs attr): value(attr.value), type(attr.group){}
    
    TValue GetValue() const {
        return value;
    }
    
    void SetValue(TValue newValue) {
        value = newValue;
    }
    
    TGroup GetType() const {
        return type;
    }
    
    void SetType(TGroup newType) {
        type = newType;
    }
    
    bool operator==(const Mark<TValue, TGroup>& other) const {
        return (type==other.GetType())&&(value==other.GetValue());
    }
};
