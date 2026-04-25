#pragma once
#include <string>

class EthernetFrame {
    public:
    EthernetFrame(std::string srcMac, std::string dstMac);
    std::string srcMac;
    std::string dstMac;
    std::string payload;
};