#pragma once

#include <random>
#include "Attribute.h"

template <typename TAttributes>
inline TAttributes GenerateRandomRoadAttributes() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> costDist(1.0, 100.0);
    std::uniform_real_distribution<float> distanceDist(0.1, 500.0);
    std::uniform_real_distribution<float> timeDist(1.0, 300.0);

    return TAttributes(
        costDist(gen),
        distanceDist(gen),
        timeDist(gen)
    );
}
