#include "commands/StepCommand.h"
#include "NetworkManager.h"
#include <string>
#include <exception>
#include <iostream>
#include <stdexcept>

void StepCommand::execute(const std::vector<std::string>& args, NetworkManager& NetManager) {
    if (args.size() < 2) {
        std::cout << "Invalid arguments for STEP. Please provide an integer value." << std::endl;
        return;
    }
    try {
        size_t processed_chars = 0;
    NetManager.simulate(std::stoi(args[1], &processed_chars));

    if (processed_chars != args[1].size()) {
        throw std::invalid_argument("Please provide an integer value.");
    }
    } catch (const std::exception& e) {
        std::cout << "Invalid arguments for STEP. Please provide an integer value." << std::endl;
    }

}
