#pragma once
#include "Transport.h"
#include "../Hash/HashTable.h"
#include <iostream>
#include <string>

namespace TransportMapper {
    // Основные функции
    TransportGroup::Types parseTransportGroup(const std::string& str);
    std::string getString(const TransportGroup& type);
    bool isValidGroupType(const std::string& str);

    TransportLine::Types parseTransportLine(const std::string& str);
    std::string getString(const TransportLine& type);
    bool isValidLineType(const std::string& str);

    // Добавление новых соответствий (расширяемость)
    void AddTransportGroupMapping(TransportGroup::Types type, const std::string& name);
    void AddTransportLineMapping(TransportLine::Types type, const std::string& name);

    // Операторы ввода/вывода
    std::ostream& operator<<(std::ostream& out, const TransportGroup& type);
    std::istream& operator>>(std::istream& in, TransportGroup& type);

    std::ostream& operator<<(std::ostream& out, const TransportLine& type);
    std::istream& operator>>(std::istream& in, TransportLine& type);
}
