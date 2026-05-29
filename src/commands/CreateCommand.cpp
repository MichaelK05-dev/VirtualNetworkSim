#include "commands/CreateCommand.h"
#include <iostream>
#include "NetworkManager.h"
#include <memory>
#include "PC.h"
#include "Hub.h"

// TO DO: Create LAN object in NetworkManager after checks ran (duplicate name,...)
void CreateCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    if (args.size() < 2) { return; }

    if (args[1] == "LAN") { // CREATE LAN(name)
        NetManager.addLAN(std::make_unique<LAN>(args[3])); // TO DO: Move LAN creation to addLAN
    } else if (args[1] == "PC") { // CREATE PC(parent_lan)
        if (args.size() >= 5) {
        for (const auto& lan : NetManager.getLANs()) {
            if (lan->getName() == args[3]) {
                std::unique_ptr<INode> node = std::make_unique<PC>();
                NetManager.addTickable(node.get());
                lan->addNode(std::move(node));
                
            }
        }
    } else if (args[1] == "HUB") { // CREATE HUB(parent_lan, portsAmount)
        if (args.size() >= 5) {
            for (const auto& lan : NetManager.getLANs()) {
                if (lan->getName() == args[3]) {
                    int portsAmount = 4;
                    if (args.size() >= 7) {
                        portsAmount= std::stoi(args[5]);
                    }
                    std::unique_ptr<INode> node = std::make_unique<Hub>(portsAmount);
                    NetManager.addTickable(node.get());
                    lan->addNode(std::move(node));
                }
        }

    } else {
        std::cout << "Failure: Invalid command or arguments." << std::endl;
    }
    }
}
}