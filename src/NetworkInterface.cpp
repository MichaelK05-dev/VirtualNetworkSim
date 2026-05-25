#include "NetworkInterface.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "EthernetBus.h"
#include "Config.h"
#include <algorithm>
#include <cmath>
#include <random>
#include "Node.h"

long long NetworkInterface::nextID = 1;

NetworkInterface::NetworkInterface(Node* parent) {
    this->parent = parent;
    generateMAC();
    connection_status =  ConnectionStatus::UNCONNECTED;
    ReceivingState = ReceivingStateEnum::SEARCHING_SFD;
    State = StateEnum::IDLE;
    connectedBus = nullptr;
}

std::string NetworkInterface::getMAC() {
    return mac_address;
}

//Generates unique 48 bit MAC address in hexadecimal 02:xx:xx:xx:xx:xx, using 02 as fixed prefix for now
void NetworkInterface::generateMAC() {
    std::stringstream mac;
    long long currentID = nextID++;
    mac << "02" << std::hex << std::setfill('0') << std::uppercase;
    for (int i = 4; i >= 0; i--) {
        mac << ":" << std::setw(2) << static_cast<int>(currentID >> (i*8) & 0xFF);
    }
    mac_address = mac.str();
}


Node* NetworkInterface::getParent() {
    return parent;
}
// TO DO: refactor to make logic easier to read
void NetworkInterface::onTick() {
    if (connection_status == ConnectionStatus::UNCONNECTED) { return;}
    lastSentBit = currentSendingBit; // save the bit from previous tick
    currentSendingBit = Signal::IDLE;

    if (State == StateEnum::IDLE && !frameQueue.empty()) { // serializing frames to bits
    serialize(frameQueue.front());
    if (!bitSendQueue.empty()) {
        State = StateEnum::SENSING;
        idleTicksCounter = 0;
    }

    }
    if (!bitSendQueue.empty()) {
    if (State == StateEnum::SENDING) {
        bool bit = bitSendQueue.front();
        currentSendingBit = (bit == true) ? Signal::ONE : Signal::ZERO;
        bitSendQueue.pop_front();
    } else if (State == StateEnum::SENSING) {
        currentSendingBit = Signal::IDLE;
    }
    } 

    if (State == StateEnum::BACKOFF) {
        if (backoffTimer <= 0) {
            State = StateEnum::IDLE;
        } else {
            backoffTimer--;
        }
    }
     connectedBus->reportSignal(currentSendingBit); 
}
// TO DO: refactor to make logic easier to read
void NetworkInterface::resolveTick() {
static std::default_random_engine generator(std::random_device{}());
if (State == StateEnum::SENDING && bitSendQueue.empty()) {
    State = StateEnum::FINISHING;
}

    if (State == StateEnum::SENSING) {
        std::cout << parent->getName() << "in sensing: " << idleTicksCounter;
        if (connectedBus->current_signal == Signal::IDLE) {
            idleTicksCounter++;
        } else {
            idleTicksCounter = 0;
        }
        if (idleTicksCounter >= Config::Ethernet::INTERFRAME_GAP_TICKS) { // TO DO: Make interframe gap random
            State = StateEnum::SENDING;
        }
        
    }
    if (lastSentBit != Signal::IDLE) {
    if (connectedBus->current_signal == Signal::COLLISION) {
       // backoff
        collisionCount++;
        bitSendQueue.clear();
        int backoff_limit = std::pow(2, std::min(collisionCount, Config::Ethernet::BACKOFF_LIMIT_K))-1;
        std::uniform_int_distribution<int> distribution(0,backoff_limit);
        int random_wait = distribution(generator);
        backoffTimer = random_wait*Config::Ethernet::SLOT_TIME_TICKS;
        std::cout << parent->getName() << ": Backoff-Ticks: " << backoffTimer;
        State = StateEnum::BACKOFF;
        currentSendingBit = Signal::IDLE;
        } else if (State == StateEnum::FINISHING) {
            frameQueue.pop();
            State = StateEnum::IDLE;
        }
    
    } 

    //Receiving logic
    switch(connectedBus->current_signal) {
        case Signal::COLLISION:
            ReceivingState = ReceivingStateEnum::SEARCHING_SFD;
            bitReceiveBuffer.clear();
            sfdWindow = 0;
            break;
        case Signal::IDLE:
            if (ReceivingState == ReceivingStateEnum::RECORDING) {
                std::unique_ptr<EthernetFrame> received_frame = deserialize();
                 std::cout << "Received payload: " << received_frame->getPayload();
                 ReceivingState = ReceivingStateEnum::SEARCHING_SFD;
                 bitReceiveBuffer.clear();
            }
            break;
        default:
            bool bit = (connectedBus->current_signal == Signal::ONE);
            if (ReceivingState == ReceivingStateEnum::SEARCHING_SFD) {
                 sfdWindow = ((sfdWindow << 1)) | bit; // always keep 8 latest bits in sfdWindow
                if (sfdWindow == 0b10101011) {
                ReceivingState = ReceivingStateEnum::RECORDING;
            }
            } else if (ReceivingState == ReceivingStateEnum::RECORDING) {
                 bitReceiveBuffer.push_back(bit);
            }
    }

}

void NetworkInterface::serialize(const std::unique_ptr<EthernetFrame>& frame) {
    bitSendQueue.clear();
    bool lastBit = false;
    //56-bit preamble
    for (int i = 0; i < 56; i++) {
        bitSendQueue.push_back(!lastBit);
        lastBit=!lastBit;
    }
    //SFD 1 byte, 10101011
    for (int i = 0; i < 8; i++) {
    if (i == 7) {
        bitSendQueue.push_back(true); 
    } else {
        bitSendQueue.push_back(!lastBit);
        lastBit = !lastBit;
    }
}
    for (bool bit : convertMACToBits(frame->getdstMac())) {
        bitSendQueue.push_back(bit);
    }
    for (bool bit : convertMACToBits(frame->getsrcMac())) {
        bitSendQueue.push_back(bit);
    }
    serializeStringToBits(frame->getPayload());
}

std::unique_ptr<EthernetFrame> NetworkInterface::deserialize() {
    std::stringstream dstMac;
    std::stringstream srcMac;
    std::string payload;
    unsigned char byte = 0;
    size_t bitPos = 0;
    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 8; j++) {
            byte = (byte << 1) | bitReceiveBuffer[bitPos];
            bitPos++;
        }
        if (i>0) { dstMac << ":";}
    dstMac << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(byte);
    byte=0;
    }
    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 8; j++) {
            byte = (byte << 1) | bitReceiveBuffer[bitPos];
            bitPos++;
        }
         if (i>0) { srcMac << ":";}
    srcMac << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(byte);
    byte=0;
    }
    while (bitPos+8 <= bitReceiveBuffer.size()) {
        char c=0;
        for (size_t i = 0; i < 8; i++) {
            c = (c << 1) | bitReceiveBuffer[bitPos];
            bitPos++;
        }
        payload += c;
    }

    return std::make_unique<EthernetFrame>(srcMac.str(), dstMac.str(), payload);

}

void NetworkInterface::connectBus(EthernetBus* bus) {
    connectedBus = bus;
    connection_status = ConnectionStatus::CONNECTED;
}


void NetworkInterface::sendFrame(std::unique_ptr<EthernetFrame> frame) {
     std::cout << "Pushed frame into queue. Payload: " << frame->getPayload();
    frameQueue.push(std::move(frame));
   

}

void NetworkInterface::serializeStringToBits(std::string inputword) {
    for (char c : inputword) {
        unsigned char byte = static_cast<unsigned char>(c);
        for (int i = 7; i >= 0; i--) {
            bitSendQueue.push_back((byte >> i) & 1);
        }
    }

}

std::vector<bool> NetworkInterface::convertMACToBits(std::string hex_string) {
    std::string delimiter = ":";
    auto pos = hex_string.find(delimiter);
    std::vector<bool> return_vector;
    while (pos != std::string::npos) {
        int byte = std::stoi(hex_string.substr(0,pos), nullptr, 16);
        for (int i = 7; i >=0; i--) {
            return_vector.push_back(byte >> i & 1);
        }
        hex_string.erase(0,pos+delimiter.length());
        pos = hex_string.find(delimiter);
    }
    if (!hex_string.empty()) {
         int byte = std::stoi(hex_string, nullptr, 16);
        for (int i = 7; i >=0; i--) {
            return_vector.push_back(byte >> i & 1);
        }
    }

    return return_vector;
}