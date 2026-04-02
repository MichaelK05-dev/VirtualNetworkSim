#include "LAN.h"
#include <memory>


LAN::LAN(std::vector<std::unique_ptr<INode>> inputNodes) {
    childs = std::move(inputNodes);
}

LAN::LAN() {
    childs = {};
}
std::vector<std::unique_ptr<INode>>& LAN::getChilds() {
    return childs;
}
