#include "PC.h"
#include <memory>
#include <iostream>

long long PC::nextPCID = 1;

PC::PC(std::string name) : Node(name) {
    addInterface();
    std::cout << name << "created" << std::endl;
}

PC::PC() : Node("PC"+std::to_string(nextPCID++)) {
    addInterface();
    std::cout << name << "created" << std::endl;
}

std::string PC::getMAC() {
    return interfaces.at(0)->getMAC();
}