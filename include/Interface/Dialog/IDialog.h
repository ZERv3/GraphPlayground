#pragma once

#include <string>

class IDialog {
public:
    static std::string ShowInputDialog(const std::string& prompt, const std::string& defaultValue = "");
};

