#include "NetworkManager.h"
#include <iostream>
#include "LAN.h"


void NetworkManager::addLAN(std::unique_ptr<LAN> inputLAN) { 

    LAN_list.push_back(std::move(inputLAN));
    std::cout << "LAN added";
}

std::vector<std::unique_ptr<LAN>>& NetworkManager::getLANs() {
    return LAN_list;
}
