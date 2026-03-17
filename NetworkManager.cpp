#include "NetworkManager.h"
#include <iostream>

void NetworkManager::addLAN(std::string name) {
    LAN_list.push_back(name);
    //std::cout << "Test1";
}

void NetworkManager::printLANs() {
    for (size_t i = 0; i < LAN_list.size(); i++) {
        std::cout << LAN_list[i];
    }
}