#pragma once
#include "commands/SendCommand.h"
#include "NetworkManager.h"
#include <string>
#include <iostream>
#include "Node.h"
#include "GlobalTypes.h"

// SEND(PC1, PC2, payload)
// TO DO: SEND(MAC_src, MAC_dest, payload) option
void SendCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    if (args.size() < 5) { std::cout << "Invalid arguments!"; return;}
    for (std::string str : args) {
        std::cout << str << " ";
    }

    if (NetManager.getNode(args.at(2)) != nullptr && NetManager.getNode(args.at(4)) != nullptr) {
       Node* SenderNode = NetManager.getNode(args.at(2));
       SenderNode->send(NetManager.getNode(args.at(4))->getMAC(), args.at(6));
       std::cout << "ran";
    }
}
