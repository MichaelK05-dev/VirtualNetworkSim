#include "EthernetBus.h"
#include <iostream>
#include "Node.h"

void EthernetBus::broadcast(EthernetFrame f) {
    for (NetworkInterface* interface : connectedInterfaces) {
        interface->receive(f);
    }
}

void EthernetBus::connect(NetworkInterface* interface) {
    if (interface != nullptr) {
        connectedInterfaces.push_back(interface);
        std::cout << "Interface " << interface->getMAC() << "belonging to " << interface->getParent()->getName() << " connected to Bus.";
    }
}