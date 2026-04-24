#include "Node.h"
#include <string>
#include <sstream>
#include <iomanip>
long long Node::nextID = 1;

Node::Node(std::string name) : name(name) {}

std::string Node::getName() {
    return name;
}

std::string Node::getMAC() {
    return mac_address;
}

//Generates unique 48 bit MAC address in hexadecimal 02:xx:xx:xx:xx:xx, using 02 as fixed prefix for now
void Node::generateMAC() {
    std::stringstream mac;
    long long currentID = nextID++;
    mac << "02" << std::hex << std::setfill('0') << std::uppercase;
    for (int i = 4; i >= 0; i--) {
        mac << ":" << std::setw(2) << static_cast<int>(currentID >> (i*8) & 0xFF);
    }
    mac_address = mac.str();
}