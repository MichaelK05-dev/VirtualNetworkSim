#include "CreateCommand.h"
#include <iostream>
#include "NetworkManager.h"
#include <memory>

void CreateCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    //std::cout << "Test0";
    if (args.size() < 2) { return; }

    if (args[1] == "LAN") {
        NetManager.addLAN(std::make_unique<LAN>(args[3]));
    }
}