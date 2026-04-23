#include "CommandManager.h"
#include <iostream>

void CommandManager::registerCommand(std::string name, ICommand* cmd) {
    if (!name.empty()) {
        commands.insert({name, cmd});
    }
   // std::cout << "worked";
}
void CommandManager::executeCommand(std::vector<std::string> tokens, NetworkManager& NetManager) {
  //  std::cout << "worked2";
    std::string command = tokens[0];
    commands.find(command)->second->execute(tokens, NetManager);
   // std::cout << "worked3";
}