#pragma once
#include <vector>
#include <string>

class NetworkManager;

class ICommand {
    public:
    virtual void execute(const std::vector<std::string>& args, NetworkManager& NetManager) = 0;
};