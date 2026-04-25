#pragma once
#include "INode.h"
#include "Node.h"

class Router : public Node {
    public:
    Router();
    Router(int portsAmount);
    private:
    static long long nextRouterID;
};