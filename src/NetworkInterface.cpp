#include "NetworkInterface.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "EthernetBus.h"

long long NetworkInterface::nextID = 1;

NetworkInterface::NetworkInterface(Node* parent) {
    this->parent = parent;
    generateMAC();
    connection_status =  ConnectionStatus::UNCONNECTED;
    connectedBus = nullptr;
}
NetworkInterface::NetworkInterface(Node* parent, EthernetBus* bus) {
    this->parent = parent;
    generateMAC();
    connection_status =  ConnectionStatus::UNCONNECTED;
    connectedBus = bus;
}

std::string NetworkInterface::getMAC() {
    return mac_address;
}

//Generates unique 48 bit MAC address in hexadecimal 02:xx:xx:xx:xx:xx, using 02 as fixed prefix for now
void NetworkInterface::generateMAC() {
    std::stringstream mac;
    long long currentID = nextID++;
    mac << "02" << std::hex << std::setfill('0') << std::uppercase;
    for (int i = 4; i >= 0; i--) {
        mac << ":" << std::setw(2) << static_cast<int>(currentID >> (i*8) & 0xFF);
    }
    mac_address = mac.str();
}


Node* NetworkInterface::getParent() {
    return parent;
}

void NetworkInterface::onTick() {
    if (!bitSendQueue.empty()) {
        State = StateEnum::SENDING;
    }

    if (State == StateEnum::SENDING) {
        bool bit = bitSendQueue.front();
        currentSendingBit = (bit == true) ? Signal::ONE : Signal::ZERO;
    } else {
        currentSendingBit = Signal::IDLE;
    }
    bitSendQueue.pop_front();
    
    
}

void NetworkInterface::resolveTick() {

}

void NetworkInterface::connectBus(EthernetBus* bus) {

}