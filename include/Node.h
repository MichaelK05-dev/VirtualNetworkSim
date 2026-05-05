#pragma once
#include "INode.h"
#include <memory>
#include <vector>
#include "ITickable.h"

class Node : public INode {
    public:
    Node(std::string name);
    std::string getName();
    std::vector<NetworkInterface*> getInterfaces(bool onlyShowUnconnected);
    void onTick() override;
    private:
    protected:
    void addInterface();
    std::vector<std::unique_ptr<NetworkInterface>> interfaces;
    std::string name;
};