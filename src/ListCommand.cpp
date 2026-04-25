#include "ListCommand.h"
#include <iostream>
#include "NetworkManager.h"
#include <memory>
#include "LAN.h"

void ListCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    if (args.size() < 2) { return; }

    if (args[1] == "LAN") {
        for (const auto& lan : NetManager.getLANs()) {
            std::cout << lan->getName()  << ", Childs: " << lan->getChilds().size() << std::endl;
        }
    }
}