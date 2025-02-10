#pragma once

#include "MacOSDialog.h"
#include "TerminalDialog.h"

#include "InterfaceStrings.h"

// Перечисление для выбора типа диалога
enum class DialogType {
    Terminal,
    MacOS
};

// Интерфейсная функция с выбором реализации
std::string ShowInputDialog(const std::string& message, DialogType type) {
    if (type == DialogType::Terminal) {
        return TerminalDialog::ShowInputDialog(message); // Вызов терминального варианта
    } else {
        return MacOSDialog::ShowInputDialog(message); // Вызов оконного варианта
    }
}

void Get(std::string& input, void (*checker)(std::string& str), std::string title, int countErrors = 3, DialogType dialog = DialogType::Terminal) {
    int attempts = 0;

    while (attempts < countErrors) {
        try {
            input = ShowInputDialog(title, dialog);
            checker(input);  // Проверка введенного значения
            return;  // Если проверка прошла успешно, выходим из функции
        } catch (const std::runtime_error& e) {
            std::cout << "[" << e.what() << "]\n";
            attempts++;
        }
    }

    std::cout << "Превышено число попыток. Возвращение в главное меню.\n";
    throw std::runtime_error("Превышено число ошибок"); // Прерываем выполнение, чтобы выйти в меню
}

int Ask(std::string title, int min, int max) {
    int choice;
    std::cout << title;
    
    while (true) {
        try{std::cin >> choice;
            // Проверка на корректный ввод
            if (std::cin.fail()) {
                std::cin.clear(); // Сбрасываем ошибку
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем ввод
                throw std::runtime_error(InterfaceStrings::incorrectInput);
            }
            
            // Проверка диапазона
            if (choice >= min && choice <= max) {
                return choice;
            }
            
            throw std::runtime_error(InterfaceStrings::incorrectInput);
        }
        catch (const std::runtime_error& e){
            std::cout << "[" << e.what() << "]\n";
            std::cout << InterfaceStrings::askChoice << std::endl;
        }
        
        
    }
}
