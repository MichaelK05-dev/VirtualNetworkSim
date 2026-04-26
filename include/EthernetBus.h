#pragma once
#include <vector>
#include "NetworkInterface.h"

class EthernetBus {

    public:
    void connect(NetworkInterface* interface);
    private:
    std::vector<NetworkInterface*> connectedInterfaces;
    void broadcast(EthernetFrame f);
};