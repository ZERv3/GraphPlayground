#include "../include/Interface/Interface.h"

#include <string>
#include <sstream>

#include <fstream>

void printFileLines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

int main() {
    setenv("TERM", "xterm-256color", 1);
    setenv("PATH", "/opt/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", 1);
    Interface<Mark<std::string, TransportGroup>, Road<RoadAttributes<RUB, Kilometre, Minute>, TransportLine>, RoadAttributes<RUB, Kilometre, Minute>> interface; interface.run();
    return 0;
}
