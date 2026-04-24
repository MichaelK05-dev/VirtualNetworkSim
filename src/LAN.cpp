#include "LAN.h"
#include <memory>


LAN::LAN(std::vector<std::unique_ptr<INode>> inputNodes) {
    childs = std::move(inputNodes);
}

LAN::LAN() {
}
LAN::LAN(std::string name) {
    this->name = name;
}
std::vector<std::unique_ptr<INode>>& LAN::getChilds() {
    return childs;
}
std::string LAN::getName() {
    return name;
}
