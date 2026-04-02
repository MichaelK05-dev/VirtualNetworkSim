#include "INetwork.h"
#include <memory>

class LAN : public INetwork {
    public:
    std::vector<std::unique_ptr<INode>>& getChilds();
    LAN(std::vector<std::unique_ptr<INode>> inputNodes);
    LAN();

    private: 
    std::vector<std::unique_ptr<INode>> childs;

};