#pragma once
#include "INetwork.h"
#include <memory>
#include "EthernetBus.h"

class LAN : public INetwork {
    public:
    std::vector<std::unique_ptr<INode>>& getChilds();
    LAN(std::vector<std::unique_ptr<INode>> inputNodes);
    LAN(std::string name);
    LAN();
    std::string getName();
    void addNode(std::unique_ptr<INode> node);

    private: 
    std::vector<std::unique_ptr<INode>> childs;
    std::string name;
    static long long nextLANID;
    std::unique_ptr<EthernetBus> bus;

};