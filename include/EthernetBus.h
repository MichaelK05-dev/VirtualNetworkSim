#pragma once
#include <vector>
#include "NetworkInterface.h"
#include "ITickable.h"
#include "GlobalTypes.h"

class EthernetBus : public ITickable {

    public:
    EthernetBus();
    void connect(NetworkInterface* interface);
    void onTick() override;
    void resolveTick() override;
    Signal current_signal;
    void reportSignal(Signal signal);
    private:
    std::vector<NetworkInterface*> connectedInterfaces;
    void broadcast(EthernetFrame f);
    int SignalsPresentThisTick;
};