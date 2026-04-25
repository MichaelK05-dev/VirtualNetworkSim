#pragma once
#include <string>
#include <optional>
#include "EthernetFrame.h"

class Node;

class NetworkInterface {
    public:
        std::string getMAC();
        NetworkInterface(Node* parent);
        void receive(EthernetFrame f);
    private:
        std::string mac_address;
        long long static nextID; // incremented for each Interface, so MACs will always be unique. TO DO: Switch to random MACs 
        void generateMAC();
        Node* parent;
        std::optional<EthernetFrame> incomingFrame;
        
};