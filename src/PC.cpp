#include "PC.h"
#include <memory>

PC::PC(std::string name) : Node(name) {
    addInterface();
}

std::string PC::getMAC() {
    return interfaces.at(0)->getMAC();
}