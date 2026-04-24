#include "Node.h"
#include <string>


Node::Node(std::string name) : name(name) {}

std::string Node::getName() {
    return name;
}

void Node::addInterface() {
    interfaces.push_back(std::make_unique<NetworkInterface>(this));
}