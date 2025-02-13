#pragma once
#include "CurrencyTypes.h"

class CurrencyConversions {
public:
    static USD ConvertToUSD(const RUB& rub, float rate = 100) {
        return USD(rub.GetValue() * rate);
    }

    static RUB ConvertToRUB(const USD& usd, float rate = 0.01) {
        return RUB(usd.GetValue() * rate);
    }
};
