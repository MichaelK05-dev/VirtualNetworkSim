#include "Node.h"
#include <string>
#include <iostream>
#include "GlobalTypes.h"


Node::Node(std::string name) : name(name) {
    
}

std::string Node::getName() {
    return name;
}

void Node::addInterface() {
    interfaces.push_back(std::make_unique<NetworkInterface>(this));
}

std::vector<NetworkInterface*> Node::getInterfaces(std::string filterParam) {
    std::vector<NetworkInterface*> return_interfaces;
    for (const auto& interface : interfaces) {
        if (filterParam  == "unconnected") {
            if (interface->connection_status == ConnectionStatus::UNCONNECTED) {
                return_interfaces.push_back(interface.get());
            }
        } else if (filterParam == "connected") {
            if (interface->connection_status == ConnectionStatus::CONNECTED) {
                return_interfaces.push_back(interface.get());
            }
        } else {
            return_interfaces.push_back(interface.get());
        }
    }
    return return_interfaces;
}

void Node::onTick() {
    std::cout << "Node ticked " << getName() << std::endl; // to be replaced
}

void Node::resolveTick() {

}

std::string Node::getMAC() {
    if (!interfaces.empty()) {
        return interfaces.at(0)->getMAC(); //not differentiating between connected/unconnected for now
    }
    return "00:00:00:00:00:00"; // fallback
}

void Node::send(std::string dest_mac, std::string payload) {
    std::unique_ptr<EthernetFrame> frame = std::make_unique<EthernetFrame>(this->getMAC(), dest_mac, payload);
    NetworkInterface* interface =  getInterfaces("connected").at(0);
    interface->sendFrame(std::move(frame));
    for (bool bit : interface->bitSendQueue) { // for debugging
        std::cout << (bit ? "1" : "0") << std::flush;
    }
    std::cout << std::endl;
}