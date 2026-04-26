#include "LAN.h"
#include <memory>
#include "PC.h"

long long LAN::nextLANID = 1;

LAN::LAN(std::vector<std::unique_ptr<INode>> inputNodes) {
    childs = std::move(inputNodes);
}

LAN::LAN() {
    this->name = "LAN"+nextLANID++; // TO DO: Check duplicates, if user added a LAN with this name before
    bus = std::make_unique<EthernetBus>();
    addNode(std::make_unique<PC>());
    
}
LAN::LAN(std::string name) {
    this->name = name;
    bus = std::make_unique<EthernetBus>();
    addNode(std::make_unique<PC>());
    
}
std::vector<std::unique_ptr<INode>>& LAN::getChilds() {
    return childs;
}
std::string LAN::getName() {
    return name;
}

void LAN::addNode(std::unique_ptr<INode> node) {
    childs.push_back(std::move(node));
    bus->connect(node->getInterfaces(true).at(0)); // Connects first available Interface to the bus as default for now
}
