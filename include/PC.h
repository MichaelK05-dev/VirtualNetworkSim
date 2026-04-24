#pragma once
#include "Node.h"
#include "NetworkInterface.h"
#include <vector>

// PC is just the generic single interface device I will be using for now
class PC : public Node {
    public:
    PC(std::string name);
    private:
};