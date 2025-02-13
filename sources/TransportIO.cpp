#include "../include/ObjectClasses/TransportIO.h"

namespace TransportMapper {
    static HashTable<std::string, TransportGroup::Types> transportGroupMap;
    static HashTable<std::string, TransportLine::Types> transportLineMap;
    static HashTable<TransportGroup::Types, std::string> groupToStringMap;
    static HashTable<TransportLine::Types, std::string> lineToStringMap;
    static bool initialized = false;

    void Initialize() {
        if (initialized) return;
        initialized = true;

        AddTransportGroupMapping(TransportGroup::BUS, "Остановка");
        AddTransportGroupMapping(TransportGroup::TRAIN, "Платформа");
        AddTransportGroupMapping(TransportGroup::SUBWAY, "Станция");
        AddTransportGroupMapping(TransportGroup::AIRPORT, "Аэропорт");

        AddTransportLineMapping(TransportLine::BUS, "Автобусная линия");
        AddTransportLineMapping(TransportLine::TRAIN, "Железнодорожная линия");
        AddTransportLineMapping(TransportLine::SUBWAY, "Линия метро");
        AddTransportLineMapping(TransportLine::AIRPORT, "Авиамаршрут");
        AddTransportLineMapping(TransportLine::WALK, "Пеший маршрут");
    }

    void AddTransportGroupMapping(TransportGroup::Types type, const std::string& name) {
        Initialize();
        transportGroupMap.Add(name, type);
        groupToStringMap.Add(type, name);
    }

    void AddTransportLineMapping(TransportLine::Types type, const std::string& name) {
        Initialize();
        transportLineMap.Add(name, type);
        lineToStringMap.Add(type, name);
    }

    TransportGroup::Types parseTransportGroup(const std::string& str) {
        Initialize();
        return transportGroupMap.Contains(str) ? transportGroupMap.GetValue(str) : TransportGroup::NONE;
    }

    std::string getString(const TransportGroup& type){
        Initialize();
        return groupToStringMap.GetValue(type.GetType());
    }

    bool isValidGroupType(const std::string& str) {
        Initialize();
        return transportGroupMap.Contains(str);
    }

    TransportLine::Types parseTransportLine(const std::string& str) {
        Initialize();
        return transportLineMap.Contains(str) ? transportLineMap.GetValue(str) : TransportLine::NONE;
    }

    std::string getString(const TransportLine& type){
        Initialize();
        return lineToStringMap.GetValue(type.GetType());
    }

    bool isValidLineType(const std::string& str) {
        Initialize();
        return transportLineMap.Contains(str);
    }

std::istream& operator>>(std::istream& in, TransportGroup& type) {
        // Пропускаем пробельные символы и ожидаем символ '<'
        char openBracket;
        in >> std::ws >> openBracket;
        if (openBracket != '<') {
            in.setstate(std::ios::failbit);
            return in;
        }

        // Считываем содержимое до символа '>'
        std::string content;
        if (!std::getline(in, content, '>')) {
            in.setstate(std::ios::failbit);
            return in;
        }

        // Преобразуем полученную строку в тип TransportGroup::Types
        TransportGroup::Types parsedType = parseTransportGroup(content);

        // Предполагается, что класс TransportGroup имеет конструктор, принимающий TransportGroup::Types
        type = TransportGroup(parsedType);

        return in;
    }

    std::istream& operator>>(std::istream& in, TransportLine& type) {
        // Пропускаем пробельные символы и ожидаем символ '<'
        char openBracket;
        in >> std::ws >> openBracket;
        if (openBracket != '<') {
            in.setstate(std::ios::failbit);
            return in;
        }

        // Считываем содержимое до символа '>'
        std::string content;
        if (!std::getline(in, content, '>')) {
            in.setstate(std::ios::failbit);
            return in;
        }

        // Преобразуем полученную строку в тип TransportLine::Types
        TransportLine::Types parsedType = parseTransportLine(content);

        // Предполагается, что класс TransportLine имеет конструктор, принимающий TransportLine::Types
        type = TransportLine(parsedType);

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const TransportGroup& type) {
        // Выводим строковое представление типа
        out << getString(type);
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const TransportLine& type) {
        // Выводим строковое представление транспортной линии
        out << getString(type);
        return out;
    }

}
