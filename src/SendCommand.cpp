#pragma once
#include "SendCommand.h"
#include "NetworkManager.h"
#include <string>
#include <iostream>

void SendCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    if (args.size() < 4) { std::cout << "Invalid arguments!"; return;}

    if (NetManager.getNode(args[1]) != nullptr && NetManager.getNode(args[3]) != nullptr) {
       // TO DO: Implement sending 
    }
}
