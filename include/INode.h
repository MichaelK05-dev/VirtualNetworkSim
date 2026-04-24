#pragma once
#include <string>
#include "NetworkInterface.h"
#include <vector>
#include <memory>
class INode {
    public:
   virtual  std::string getName() = 0;
   virtual  std::string getMAC() = 0;

    private:
    std::string name;
    std::string mac_address;
    virtual void addInterface() = 0;
    std::vector<std::unique_ptr<NetworkInterface>> interfaces;
};