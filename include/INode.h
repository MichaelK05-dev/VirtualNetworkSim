#pragma once
#include <string>
#include "NetworkInterface.h"
#include <vector>
#include <memory>
#include "ITickable.h"
class INode : public ITickable {
    public:
   virtual  std::string getName() = 0;
   virtual  std::string getMAC() = 0;
    virtual std::vector<NetworkInterface*> getInterfaces(std::string filterParam="") = 0;
    virtual ~INode() = default;
    private:
    std::string name;
    std::string mac_address;
    virtual void addInterface() = 0;
    std::vector<std::unique_ptr<NetworkInterface>> interfaces;
};