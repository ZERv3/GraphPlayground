#pragma once

class TransportGroup {
public:
    enum Types {NONE, BUS, TRAIN, SUBWAY, AIRPORT};
        
    explicit TransportGroup(Types type) : type(type) {}
    explicit TransportGroup() : type(Types()) {}

    Types GetType() const { return type; }
    
    bool operator==(const TransportGroup& other){
        return (type == other.GetType());
    }
    
private:
    Types type;
};

class TransportLine {
public:
    enum Types {NONE, BUS, TRAIN, SUBWAY, AIRPORT, WALK};
    
    explicit TransportLine(Types type) : type(type){}
    explicit TransportLine() : type(Types()){}
    
    Types GetType() const {return type;}
    
    bool operator==(const TransportLine& other){
        return (type == other.GetType());
    }
    
private:
    Types type;
};
