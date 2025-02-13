#pragma once
#include "Mark.h"
#include "../Transport.h"

#include <string>
#include <random>

inline std::string GenerateRandomString() {
    static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string digits = "0123456789";
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> letterDist(0, letters.size() - 1);
    std::uniform_int_distribution<> digitDist(0, digits.size() - 1);

    std::string randomString;
    
    // Генерация формата A000AA
    randomString += letters[letterDist(gen)]; // Первая буква
    randomString += digits[digitDist(gen)];   // Первая цифра
    randomString += digits[digitDist(gen)];   // Вторая цифра
    randomString += digits[digitDist(gen)];   // Третья цифра
    randomString += letters[letterDist(gen)]; // Вторая буква
    randomString += letters[letterDist(gen)]; // Третья буква

    return randomString;
}

inline Mark<std::string, TransportGroup> GenerateRandomMark() {
    // Генерация случайного имени в формате A000AA
    std::string randomValue = GenerateRandomString();

    // Выбор случайного типа TransportGroup
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDist(1, 4); // Исключаем NONE (0)
    TransportGroup randomGroup(static_cast<TransportGroup::Types>(typeDist(gen)));

    return Mark<std::string, TransportGroup>(randomValue, randomGroup);
}

// Mark<std::string, TransportGroup> randMark = GenerateRandomMark();
