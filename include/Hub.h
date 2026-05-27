#pragma once
#include "Node.h"

class Hub : public Node {
    Hub(int ports=4);
    void onTick() override;
    void resolveTick() override;
    
    private:
    static long long nextPCID;
};