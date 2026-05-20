#pragma once
#include <string>
#include <optional>
#include "EthernetFrame.h"
#include <queue>
#include "ITickable.h"
#include "GlobalTypes.h"
#include <memory>


class Node;
class EthernetBus;

class NetworkInterface : public ITickable {
    public:
        std::string getMAC();
        NetworkInterface(Node* parent);
        Node* getParent();
        enum class StateEnum {IDLE, PREPARING, SENSING, SENDING, RECEIVING, BACKOFF};
        ConnectionStatus connection_status;
        StateEnum State;
        std::deque<bool> bitReceiveBuffer;
        std::deque<bool> bitSendQueue;
        void onTick();
        void resolveTick();
        void connectBus(EthernetBus* bus);
        void sendFrame(std::unique_ptr<EthernetFrame>);
    private:
        std::string mac_address;
        long long static nextID; // incremented for each Interface, so MACs will always be unique. TO DO: Switch to random MACs 
        void generateMAC();
        Node* parent;
        Signal currentSendingBit;
        Signal lastSentBit;
        EthernetBus* connectedBus;
        void serializeStringToBits(std::string inputword);
        std::vector<bool> convertMACToBits(std::string hex_string);
       
        
};