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
    Signal current_signal = Signal::IDLE;
    void reportSignal(Signal signal);
    void prepareNewTick();
    std::vector<NetworkInterface*> connectedInterfaces;
    private:
    void broadcast(EthernetFrame f);
    int SignalsPresentThisTick = 0;
    Signal writing_signal = Signal::IDLE;
};