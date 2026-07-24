#pragma once
#include <vector>
#include <string>
#include "LAN.h"

// to be expanded
class NetworkManager {
    public:
    void addLAN(std::unique_ptr<LAN> inputLAN);
    void addCable(std::unique_ptr<EthernetBus> inputCable);
    std::vector<std::unique_ptr<LAN>>& getLANs();
    LAN* getLAN(std::string name);
    long long currentTick = 0;
    void simulate(int steps);
    void simulate (std::string mode ="CONTINUOUSLY", int max_ticks=Config::Debug::max_tries);
    void addTickable(ITickable* tickable);
    std::vector<ITickable*>& getTickables();
    Node* getNode(std::string name);
    
    private:
    std::vector<std::unique_ptr<LAN>> LAN_list;
    std::vector<std::unique_ptr<EthernetBus>> cable_list; // TO DO: Move to abstract cable type for unique ptr
    std::vector<ITickable*> tickable_list;
};