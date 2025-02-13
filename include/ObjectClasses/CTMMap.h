#pragma once

#include <string>

enum CTMAttributes{CURRENCY, METRICS, TIME, NONE};

namespace AttributeMapper {
    CTMAttributes ParseAttribute(const std::string& str);
    std::string ToString(CTMAttributes attr);
    void AddCTMAttrMapping(CTMAttributes attr,const std::string& str);
    void Initialize();
}

bool isValidAttribute(const std::string& str);
