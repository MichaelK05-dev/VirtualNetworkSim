#include "Node.h"
#include <string>


Node::Node(std::string name) : name(name) {}

std::string Node::getName() {
    return name;
}

void Node::addInterface() {
    interfaces.push_back(std::make_unique<NetworkInterface>(this));
}

std::vector<NetworkInterface*> Node::getInterfaces(bool onlyShowUnconnected) {
    std::vector<NetworkInterface*> return_interfaces;
    for (const auto& interface : interfaces) {
        if (onlyShowUnconnected == true) {
            if (interface->connection_status == NetworkInterface::ConnectionStatus::UNCONNECTED) {
                return_interfaces.push_back(interface.get());
            }
        } else {
            return_interfaces.push_back(interface.get());
        }
    }
}