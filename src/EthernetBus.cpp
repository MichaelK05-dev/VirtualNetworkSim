#include "EthernetBus.h"
#include <iostream>
#include "Node.h"

EthernetBus::EthernetBus() {
    
}

void EthernetBus::broadcast(EthernetFrame f) {
  
}

void EthernetBus::connect(NetworkInterface* interface) {
    if (interface != nullptr) {
        connectedInterfaces.push_back(interface);
        std::cout << "Interface " << interface->getMAC() << "belonging to " << interface->getParent()->getName() << " connected to Bus." << std::endl;
    }
}

void EthernetBus::onTick() {
    
}

void EthernetBus::resolveTick() {
    
}