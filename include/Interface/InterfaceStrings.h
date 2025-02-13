#pragma once
#include <string>

namespace InterfaceStrings {
    extern const std::string title;
    extern const std::string getDialogTypeTitle;
    extern const std::string askChoice;
    extern const std::string askValue;
    extern const std::string getVertexCountTitle;
    extern const std::string getEdgesCountTitle;
    extern const std::string getStepCountTitle;
    extern const std::string getDifficultyTitle;

    // Ошибки
    extern const std::string incorrectInput;
    extern const std::string usedKeySymbols;
    extern const std::string objectTypeNotExists;
    extern const std::string objectExists;
    extern const std::string objectNotExists;
    extern const std::string objectAimsSelf;

    //Главное меню
    extern const std::string mainMenuTitle;
    extern const std::string mainMenuOptions;

    // Меню редактирования
    extern const std::string handMenuTitle;
    extern const std::string handMenuOptions;

    // Меню нагрузочных тестов
    extern const std::string loadTestsMenuTitle;
    extern const std::string loadTestsMenuOptions;

    // Запросы
    extern const std::string getObjectTypeTitle;
    extern const std::string getObjectNameTitle;

    // Типы объектов
    extern const std::string markTypes;
    extern const std::string roadTypes;
    extern const std::string getAttributeTitle;
    extern const std::string attributes;
}
