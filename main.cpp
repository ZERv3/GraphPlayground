#include "Interface/Interface.h"

#include <string>
#include <sstream>

int main() {
//    setenv("PATH", "/opt/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", 1);
    Interface<Mark<std::string, TransportGroup>, Road<RoadAttributes<RUB, Kilometre, Minute>, TransportLine>, RoadAttributes<RUB, Kilometre, Minute>> interface; interface.run();
    return 0;
}

