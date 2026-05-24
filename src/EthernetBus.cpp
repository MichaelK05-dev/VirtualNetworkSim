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

void EthernetBus::prepareNewTick() {
    current_signal = writing_signal;
    writing_signal = Signal::IDLE;
    SignalsPresentThisTick = 0;
    std::cout << "Signal: "<< (((current_signal==Signal::ONE) ? "one -" : (current_signal==Signal::ZERO) ? "zero -" : ((current_signal==Signal::COLLISION) ? "collision -" : "idle -"))) << std::endl;
}
void EthernetBus::reportSignal(Signal s) {
   if (s == Signal::IDLE) return;
   SignalsPresentThisTick++;
   writing_signal = (SignalsPresentThisTick > 1) ? Signal::COLLISION : s;
}