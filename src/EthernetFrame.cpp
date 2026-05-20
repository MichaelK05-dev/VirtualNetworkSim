#include "EthernetFrame.h"

EthernetFrame::EthernetFrame(std::string srcMac, std::string dstMac, std::string payload) : srcMac{srcMac}, dstMac{dstMac}, payload{payload} {}

std::string EthernetFrame::getsrcMac() {
    return srcMac;
}

std::string EthernetFrame::getdstMac() {
    return dstMac;
}

std::string EthernetFrame::getPayload() {
    return payload;
}