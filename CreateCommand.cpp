#include "CreateCommand.h"
#include <iostream>
#include "NetworkManager.h"

void CreateCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    //std::cout << "Test0";
    if (args.size() < 2) { return; }

    if (args[1] == "LAN") {
        NetManager.addLAN(args[3]);
    }
}