#pragma once
#include "Node.h"

class Hub : public Node {
    public:
    Hub(int ports=4);
    void onTick() override;
    void resolveTick() override;
    static long long nextPCID;
};