#include "NetworkInterface.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "EthernetBus.h"

long long NetworkInterface::nextID = 1;

NetworkInterface::NetworkInterface(Node* parent) {
    this->parent = parent;
    generateMAC();
    connection_status =  ConnectionStatus::UNCONNECTED;
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

void NetworkInterface::onTick() {
    if (!bitSendQueue.empty()) {
        State = StateEnum::SENDING;
    }

    if (State == StateEnum::SENDING) {
        bool bit = bitSendQueue.front();
        currentSendingBit = (bit == true) ? Signal::ONE : Signal::ZERO;
        std::cout << (bit ? "1" : "0") << std::flush;
        bitSendQueue.pop_front();
    } else {
        currentSendingBit = Signal::IDLE;
    }
    
    std::cout << std::endl;
    
}

void NetworkInterface::resolveTick() {

}

void NetworkInterface::connectBus(EthernetBus* bus) {
    connectedBus = bus;
    connection_status = ConnectionStatus::CONNECTED;
}


void NetworkInterface::sendFrame(std::unique_ptr<EthernetFrame> frame) {
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