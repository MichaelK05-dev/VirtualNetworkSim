#include "ListCommand.h"
#include <iostream>
#include "NetworkManager.h"
#include <memory>
#include "LAN.h"
#include "Node.h"

void ListCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    if (args.size() < 2) { return; }

    if (args[1] == "LAN") {
        for (const auto& lan : NetManager.getLANs()) {
            std::cout << lan->getName()  << ", Childs: " << lan->getChilds().size() << std::endl;
        }
    }
    if (args[1] == "NODE") {
        for (auto* ITickable : NetManager.getTickables()) {
           if (Node* validNode = dynamic_cast<Node*>(ITickable)) {
                std::cout << validNode->getName() << std::endl;
           }
        }
    }
}