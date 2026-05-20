#pragma once
#include "INode.h"
#include <memory>
#include <vector>
#include "ITickable.h"

class Node : public INode {
    public:
    Node(std::string name);
    std::string getName() override;
    std::string getMAC() override;
    std::vector<NetworkInterface*> getInterfaces(std::string filterParam) override;
    void onTick() override;
    void resolveTick() override; // eventually private
    void send(std::string dest_mac, std::string payload);
    private:
    protected:
    void addInterface();
    std::vector<std::unique_ptr<NetworkInterface>> interfaces;
    std::string name;
};