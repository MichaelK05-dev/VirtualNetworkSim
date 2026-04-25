#pragma once
#include "INode.h"
#include <memory>
#include <vector>
class Node : public INode {
    public:
    Node(std::string name);
    std::string getName();
    private:
    protected:
    void addInterface();
    std::vector<std::unique_ptr<NetworkInterface>> interfaces;
    std::string name;
};