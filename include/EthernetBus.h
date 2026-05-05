#pragma once
#include <vector>
#include "NetworkInterface.h"
#include "ITickable.h"

class EthernetBus : public ITickable {

    public:
    void connect(NetworkInterface* interface);
    void onTick() override;
    void resolveTick() override;
    private:
    std::vector<NetworkInterface*> connectedInterfaces;
    void broadcast(EthernetFrame f);
};