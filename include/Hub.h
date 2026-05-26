#pragma once
#include "Node.h"

class Hub : public Node {
    Hub(std::string name, int ports=4);
    void onTick() override;
    void resolveTick() override;
};