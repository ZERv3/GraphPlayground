#include "CTMMap.h"
#include "../Hash/HashTable.h"

namespace AttributeMapper {
static HashTable<std::string, CTMAttributes> attributeMap;
static HashTable<CTMAttributes, std::string> attributeToStringMap;

static bool initialized = false;

void Initialize() {
    if(initialized) return;
    initialized = true;
    
    AddCTMAttrMapping(CTMAttributes::CURRENCY, "Стоимость");
    AddCTMAttrMapping(CTMAttributes::TIME, "Время");
    AddCTMAttrMapping(CTMAttributes::METRICS, "Метрика");
}

void AddCTMAttrMapping(CTMAttributes attr, const std::string& str){
    Initialize();
    attributeToStringMap.Add(attr, str);
    attributeMap.Add(str,attr);
}

CTMAttributes ParseAttribute(const std::string& str){
    Initialize();
    return attributeMap.Contains(str) ? attributeMap.GetValue(str) : CTMAttributes::NONE;
}

std::string ToString(CTMAttributes attr){
    Initialize();
    return attributeToStringMap.GetValue(attr);
}
}
bool isValidAttribute(const std::string& str){
    return AttributeMapper::ParseAttribute(str) != CTMAttributes::NONE;
}
