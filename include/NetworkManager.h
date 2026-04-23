#pragma once
#include <vector>
#include <string>
#include "LAN.h"

// to be expanded
class NetworkManager {
    public:
    void addLAN(std::unique_ptr<LAN> inputLAN);
    std::vector<std::unique_ptr<LAN>>& getLANs();
    
    private:
    std::vector<std::unique_ptr<LAN>> LAN_list;
};