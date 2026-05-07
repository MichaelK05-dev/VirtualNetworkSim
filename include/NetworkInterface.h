#pragma once
#include <string>
#include <optional>
#include "EthernetFrame.h"
#include <queue>
#include "ITickable.h"

class Node;

class NetworkInterface : public ITickable {
    public:
        std::string getMAC();
        NetworkInterface(Node* parent);
        Node* getParent();
        enum class ConnectionStatus {CONNECTED, UNCONNECTED};
        ConnectionStatus connection_status;
        std::queue<bool> bitReceiveBuffer;
        std::queue<bool> bitSendQueue;
        void onTick();
        void resolveTick();
    private:
        std::string mac_address;
        long long static nextID; // incremented for each Interface, so MACs will always be unique. TO DO: Switch to random MACs 
        void generateMAC();
        Node* parent;
       
        
};