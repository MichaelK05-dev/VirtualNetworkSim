#include "NetworkInterface.h"
#include <iostream>
#include <iomanip>
#include <sstream>

long long NetworkInterface::nextID = 1;

NetworkInterface::NetworkInterface(Node* parent) {
    this->parent = parent;
    generateMAC();
    incomingFrame = std::nullopt;
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

void NetworkInterface::receive(EthernetFrame f) {
    if (f.srcMac == this->mac_address) {
    incomingFrame = f;
    }
}

Node* NetworkInterface::getParent() {
    return parent;
}