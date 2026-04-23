#pragma once
#include "INode.h"
class Node : public INode {
    public:
    std::string getName();
    std::string getIP();
    private:
    std::string name;
    std::string ip;
};