#pragma once
#include <vector>
#include "NetworkInterface.h"

class EthernetBus {

    public:
    private:
    std::vector<NetworkInterface*> connectedInterfaces;
    void broadcast(EthernetFrame f);
};