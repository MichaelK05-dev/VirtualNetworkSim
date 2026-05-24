#include "NetworkManager.h"
#include <iostream>
#include "LAN.h"
#include <algorithm>
#include "Node.h"


void NetworkManager::addLAN(std::unique_ptr<LAN> inputLAN) { 
    auto it = std::find_if(LAN_list.begin(), LAN_list.end(), [&](std::unique_ptr<LAN>& lan){return lan->getName() == inputLAN->getName();});
    if (it == LAN_list.end()) {
        tickable_list.push_back(inputLAN->getEthernetBus());
        for (auto& childs : inputLAN->getChilds()) {
            tickable_list.push_back(childs.get());
        }
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

void NetworkManager::simulate(int steps) {
    std::cout << "DEBUG: Anzahl Objekte in tickable_list: " << tickable_list.size() << std::endl;
    for (int i = 0; i < steps; i++) {

    for (const auto& tickable : tickable_list) { 
       
        if (auto* bus = dynamic_cast<EthernetBus*>(tickable)) {
            bus->prepareNewTick();
        }
    }
    for (const auto& tickable : tickable_list) { 
        tickable->onTick();
    }
    std::cout << "done with onticks";
    for (const auto& tickable : tickable_list) { 
        tickable->resolveTick();
    }
    std::cout << "done with resolveticks";
    }
    
}

void NetworkManager::addTickable(ITickable* tickable) {
    tickable_list.push_back(tickable);
}

std::vector<ITickable*> NetworkManager::getTickables() {
    return tickable_list;
}

Node* NetworkManager::getNode(std::string name) {
    for (auto* tickable : tickable_list) {
        if (Node* casted_node = dynamic_cast<Node*>(tickable)) {
            if (casted_node->getName() == name) {
                return casted_node;
            }
        }
    }
    return nullptr;
}