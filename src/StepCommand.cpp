#include "StepCommand.h"
#include "NetworkManager.h"
#include <string>

void StepCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    NetManager.simulate(std::stoi(args[1]));

}
