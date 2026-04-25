#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"
#include "CommandManager.h"
#include "NetworkManager.h"
#include "CreateCommand.h"
#include "ListCommand.h"


int main() {

    std::string commandinput;
    std::cout << "Enter commands: " << std::endl;

//for (size_t j = 0; j < parameters_tokenized.size(); j++) {
  //     std::cout << parameters_tokenized.at(j)+" ";
  // }

   NetworkManager n1;
   CommandManager c1;
   c1.registerCommand("CREATE", new CreateCommand());
   c1.registerCommand("LIST", new ListCommand());
   

while (true) {
    std::cout << "NetSim> " << std::flush;
    std::getline(std::cin, commandinput);
    if (commandinput == "exit") { 
        std::cout << "Exited program";
        break; 
    }
    std::vector<std::string> parameters_tokenized = Parser::tokenize(commandinput);
    if (!parameters_tokenized.empty()) {
    c1.executeCommand(parameters_tokenized, n1);
    } 
}

    return 0;
}