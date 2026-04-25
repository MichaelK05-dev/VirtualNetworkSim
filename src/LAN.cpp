#include "LAN.h"
#include <memory>
#include "PC.h"


LAN::LAN(std::vector<std::unique_ptr<INode>> inputNodes) {
    childs = std::move(inputNodes);
}

LAN::LAN() {
}
LAN::LAN(std::string name) {
    this->name = name;
    childs.push_back(std::make_unique<PC>("PC"+std::to_string(childs.size()+1)));
}
std::vector<std::unique_ptr<INode>>& LAN::getChilds() {
    return childs;
}
std::string LAN::getName() {
    return name;
}
