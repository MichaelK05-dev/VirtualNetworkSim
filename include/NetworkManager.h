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
    
    private:
    std::vector<std::unique_ptr<LAN>> LAN_list;
};