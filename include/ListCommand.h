#pragma once
#include "ICommand.h"

class ListCommand : public ICommand {
    public:
    void execute(const std::vector<std::string>& args, NetworkManager& NetManager) override;
};