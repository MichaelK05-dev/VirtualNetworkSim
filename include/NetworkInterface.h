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
        enum class StateEnum {IDLE, PREPARING, SENSING, SENDING, RECEIVING, BACKOFF, FINISHING};
        enum class ReceivingStateEnum {SEARCHING_SFD, RECORDING};
        ConnectionStatus connection_status;
        StateEnum State;
        ReceivingStateEnum ReceivingState;
        std::deque<bool> bitReceiveBuffer;
        std::deque<bool> bitSendQueue;
        std::queue<std::unique_ptr<EthernetFrame>> frameQueue;
        void onTick() override;
        void resolveTick() override;
        void connectBus(EthernetBus* bus);
        void sendFrame(std::unique_ptr<EthernetFrame>);
        void serialize(const std::unique_ptr<EthernetFrame>& frame);
        std::unique_ptr<EthernetFrame> deserialize();
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
        int idleTicksCounter = 0;
        unsigned char sfdWindow = 0; // used to check for SFD
        int collisionCount = 0;;
        int backoffTimer = 0;
       
        
};