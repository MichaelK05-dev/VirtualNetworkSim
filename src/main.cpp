#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"
#include "CommandManager.h"
#include "NetworkManager.h"
#include "CreateCommand.h"


int main() {

    std::string commandinput;
    std::getline(std::cin, commandinput);
    std::vector<std::string> parameters_tokenized = Parser::tokenize(commandinput);

for (size_t j = 0; j < parameters_tokenized.size(); j++) {
       std::cout << parameters_tokenized.at(j)+" ";
   }

   NetworkManager n1;
   CommandManager c1;
   c1.registerCommand("CREATE", new CreateCommand());
   c1.executeCommand(parameters_tokenized, n1);

    return 0;
}