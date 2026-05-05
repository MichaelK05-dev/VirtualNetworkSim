#pragma once
#include <memory>
#include <vector>
#include "INode.h"
class INetwork {
public:
   virtual std::vector<std::unique_ptr<INode>>& getChilds() = 0;
   virtual ~INetwork() = default;

private: 
    std::vector<std::unique_ptr<INode>> childs;

};
