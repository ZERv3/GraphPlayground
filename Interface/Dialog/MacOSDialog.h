#pragma once

#include "IDialog.h"

#include <sstream>
#include <cstdio>
#include <cstdlib>

class MacOSDialog : public IDialog {
public:
    static std::string ShowInputDialog(const std::string& prompt) {
        std::ostringstream script;
        
        script << "osascript -e '"
        << "tell application \"System Events\" to display dialog \""
        << prompt
        << "\" default answer \""
        << ""
        << "\" with icon note'";
        
        FILE* pipe = popen(script.str().c_str(), "r");
        if (!pipe) return "";
        
        char buffer[256];
        std::string result;
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        
        pclose(pipe);
        
        // Извлекаем только введенный текст, убирая лишние части вывода AppleScript
        size_t pos = result.find("text returned:");
        if (pos != std::string::npos) {
            result = result.substr(pos + 14);
        }
        
        // Убираем лишние символы (переносы строк, пробелы)
        result.erase(result.find_last_not_of(" \n\r\t") + 1);
        
        return result;
    }
};

