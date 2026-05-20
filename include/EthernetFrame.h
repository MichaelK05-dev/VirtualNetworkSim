#pragma once
#include <string>

class EthernetFrame {
    public:
    EthernetFrame(std::string srcMac, std::string dstMac, std::string payload);
    std::string getsrcMac();
    std::string getdstMac();
    std::string getPayload();

    private:
    std::string srcMac;
    std::string dstMac;
    std::string payload;

};