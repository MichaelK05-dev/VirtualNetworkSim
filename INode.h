#pragma once
#include <string>
class INode {
    public:
   virtual  std::string getName() = 0;
   virtual  std::string getIP() = 0;

    private:
    std::string name;
    std::string ip;
};