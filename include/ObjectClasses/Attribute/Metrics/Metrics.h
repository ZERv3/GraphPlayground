#pragma once
#include "MetricsTypes.h"

class MetricsConversions {
public:
    static Metre ConvertToMetres(const Kilometre& km) {
        return Metre(km.GetValue() * 1000);
    }

    static Kilometre ConvertToKilometres(const Metre& m) {
        return Kilometre(m.GetValue() / 1000.0);
    }
};
