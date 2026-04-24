#pragma once
#include <string>

class Node;

class NetworkInterface {
    public:
        std::string getMAC();
        NetworkInterface(Node* parent);
    private:
        std::string mac_address;
        long long static nextID; // incremented for each Interface, so MACs will always be unique. TO DO: Switch to random MACs 
        void generateMAC();
        Node* parent;
};