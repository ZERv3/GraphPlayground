#pragma once

#include <random>
#include "Road.h"
#include "RoadAttributes.h"
#include "../Transport.h"
#include "../Attribute/AttributeGen.h" // Подключаем генератор атрибутов

template <typename TAttributes>
inline Road<TAttributes, TransportLine> GenerateRandomRoad() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Генерируем случайные RoadAttributes
    TAttributes randomAttributes = GenerateRandomRoadAttributes<TAttributes>();

    // Генерация случайного типа дороги (TransportLine)
    std::uniform_int_distribution<int> typeDist(1, static_cast<int>(TransportLine::Types::WALK));
    TransportLine randomType(static_cast<TransportLine::Types>(typeDist(gen)));

    return Road<TAttributes, TransportLine>(randomAttributes, randomType);
}

// auto road = GenerateRandomRoad<RUB, Kilometre, Minute>();
