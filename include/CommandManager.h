#pragma once
#include <map>
#include <string>
#include "ICommand.h"

class CommandManager {
    public:
    void registerCommand(std::string name, ICommand* cmd);
    void executeCommand(std::vector<std::string> tokens, NetworkManager& NetManager);
    private:
    std::map<std::string, ICommand*> commands;
};