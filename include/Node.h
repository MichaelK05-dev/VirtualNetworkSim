#pragma once
#include "INode.h"
class Node : public INode {
    public:
    Node(std::string name);
    std::string getName();
    std::string getMAC();
    private:
    std::string name;
    std::string mac_address;
    long long static nextID; // incremented for each Node, so MACs will always be unique. TO DO: Switch to random MACs 
    void generateMAC();
};