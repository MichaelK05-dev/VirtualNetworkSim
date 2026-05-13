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
        interface->connectBus(this);
        std::cout << "Interface " << interface->getMAC() << "belonging to " << interface->getParent()->getName() << " connected to Bus." << std::endl;
    }
}

void EthernetBus::onTick() {
    
}

void EthernetBus::resolveTick() {
    
}

void EthernetBus::reportSignal(Signal signal) {
    SignalsPresentThisTick++;
    if (SignalsPresentThisTick > 1) {
        current_signal = Signal::COLLISION;
    } else {
        current_signal = signal;
    }
}