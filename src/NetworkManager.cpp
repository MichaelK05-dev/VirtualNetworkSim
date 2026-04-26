#include "NetworkManager.h"
#include <iostream>
#include "LAN.h"
#include <algorithm>


void NetworkManager::addLAN(std::unique_ptr<LAN> inputLAN) { 
    auto it = std::find_if(LAN_list.begin(), LAN_list.end(), [&](std::unique_ptr<LAN>& lan){return lan->getName() == inputLAN->getName();});
    if (it == LAN_list.end()) {
        LAN_list.push_back(std::move(inputLAN));
        std::cout << "LAN added" << std::endl;
    } else {
        std::cout << "Failure: LAN with name " << "\"" << (*it)->getName() << "\"" << "already exists.";
    }
    
}

std::vector<std::unique_ptr<LAN>>& NetworkManager::getLANs() {
    return LAN_list;
}

LAN* NetworkManager::getLAN(std::string name) {
    for (const auto& lan : LAN_list) {
        if (lan->getName() == name) {
            return lan.get();
        }
    }
    return nullptr;
}