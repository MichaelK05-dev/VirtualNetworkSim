#pragma once
#include <string>
#include <optional>
#include "EthernetFrame.h"
#include <queue>
#include "ITickable.h"
#include "GlobalTypes.h"


class Node;
class EthernetBus;

class NetworkInterface : public ITickable {
    public:
        std::string getMAC();
        NetworkInterface(Node* parent);
        NetworkInterface(Node* parent, EthernetBus* bus);
        Node* getParent();
        enum class StateEnum {IDLE, PREPARING, SENSING, SENDING, RECEIVING, BACKOFF};
        ConnectionStatus connection_status;
        StateEnum State;
        std::deque<bool> bitReceiveBuffer;
        std::deque<bool> bitSendQueue;
        void onTick();
        void resolveTick();
        void connectBus(EthernetBus* bus);
    private:
        std::string mac_address;
        long long static nextID; // incremented for each Interface, so MACs will always be unique. TO DO: Switch to random MACs 
        void generateMAC();
        Node* parent;
        Signal currentSendingBit;
        Signal lastSentBit;
        EthernetBus* connectedBus;
       
        
};