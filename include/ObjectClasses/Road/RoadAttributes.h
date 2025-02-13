#pragma once

template <typename TCurrency, typename TMetrics, typename TTime>
class RoadAttributes{
private:
    TCurrency cost;
    TMetrics distance;
    TTime time;
public:
    RoadAttributes():
        cost(TCurrency()),
        distance(TMetrics()),
        time(TTime()){}
    
    RoadAttributes(TCurrency cost, TMetrics distance, TTime time):
        cost(cost),
        distance(distance),
        time(time){}
    
    RoadAttributes(double cost, double distance, double time):
        cost(cost),
        distance(distance),
        time(time){}
    
    TCurrency GetCost() const {
        return cost;
    }
    
    TMetrics GetDistance() const {
        return distance;
    }
    
    TTime GetTime() const {
        return time;
    }
    
    void SetCost(TCurrency newCost) {
        this->cost = newCost;
    }
    void SetDistance(TMetrics newDistance) {
        this->distance = newDistance;
    }
    void SetTime(TTime newTime) {
        this->time = newTime;
    }
    
    bool operator==(const RoadAttributes& other) const {
        return time == other.time && cost == other.cost && distance == other.distance;
    }
    
    // Перегрузка оператора +
    RoadAttributes operator+(RoadAttributes& other) {
        TCurrency newCost = TCurrency(cost.GetValue() + other.cost.GetValue());
        TMetrics newDistance = TMetrics(distance.GetValue() + other.distance.GetValue());
        TTime newTime = TTime(time.GetValue() + other.time.GetValue());
        
        return RoadAttributes(newCost, newDistance, newTime);
    }
    
    static RoadAttributes<TCurrency, TMetrics, TTime> max(){
        return RoadAttributes<TCurrency, TMetrics, TTime>(
                                                          TCurrency::max(),
                                                          TMetrics::max(),
                                                          TTime::max()
                                                          );
    }
};

