#include "CommandManager.h"
#include <iostream>

void CommandManager::registerCommand(std::string name, ICommand* cmd) {
    if (!name.empty()) {
        commands.insert({name, cmd});
    }
}
void CommandManager::executeCommand(std::vector<std::string> tokens, NetworkManager& NetManager) {
    if(tokens.empty()) return; 

    std::string command = tokens[0];
    auto it = commands.find(command);
    if (it != commands.end()) {
      it->second->execute(tokens,NetManager);
    } else {
      std::cout << "Invalid command \"" << command << "\"" << std::endl;
    }

}