#include "CreateCommand.h"
#include <iostream>
#include "NetworkManager.h"
#include <memory>
#include "PC.h"

// TO DO: Create LAN object in NetworkManager after checks ran (duplicate name,...)
void CreateCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    if (args.size() < 2) { return; }

    if (args[1] == "LAN") {
        NetManager.addLAN(std::make_unique<LAN>(args[3]));
    }
    if (args[1] == "PC") {
        if (args.size() >= 5) {
        for (const auto& lan : NetManager.getLANs()) {
            if (lan->getName() == args[3]) {
                lan->addNode(std::make_unique<PC>());
            }
        }
    } else {
        std::cout << "Failure: You need to specify a parent LAN to create Node." << std::endl;
    }
    }
}