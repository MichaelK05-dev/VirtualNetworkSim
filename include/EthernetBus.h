#pragma once
#include <vector>
#include "NetworkInterface.h"
#include "ITickable.h"

class EthernetBus : public ITickable {

    public:
    EthernetBus();
    void connect(NetworkInterface* interface);
    void onTick() override;
    void resolveTick() override;
    enum class Signal {IDLE, ZERO, ONE, COLLISSION};
    private:
    std::vector<NetworkInterface*> connectedInterfaces;
    void broadcast(EthernetFrame f);
};