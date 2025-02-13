#pragma once

#include "IDialog.h"

#include <iostream>

class TerminalDialog : public IDialog {
public:
    static std::string ShowInputDialog(const std::string& message) {
        std::cout << message << ": ";
        std::string input;
        
        if (std::cin.peek() == '\n') {
            std::cin.ignore();  // Игнорируем оставшийся '\n' только если он есть
        }
        
        std::getline(std::cin, input);
        
        return input; // Теперь можно просто нажать Enter и получить ""
    }
};
