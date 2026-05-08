#pragma once
#include <vector>
#include <string>
#include "LAN.h"

// to be expanded
class NetworkManager {
    public:
    void addLAN(std::unique_ptr<LAN> inputLAN);
    std::vector<std::unique_ptr<LAN>>& getLANs();
    LAN* getLAN(std::string name);
    long long currentTick = 0;
    void simulate(int steps);
    void addTickable(ITickable* tickable);
    std::vector<ITickable*> getTickables();
    
    private:
    std::vector<std::unique_ptr<LAN>> LAN_list;
    std::vector<ITickable*> tickable_list;
};