#pragma once
#include "TimeTypes.h"

class TimeConversions {
public:
    static Hour ConvertToHour(const Minute& m) {
        return Hour(m.GetValue() / 60.0);
    }

    static Minute ConvertToKilometres(const Hour& h) {
        return Minute(h.GetValue() * 60);
    }
};
