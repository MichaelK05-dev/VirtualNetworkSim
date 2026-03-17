#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"


int main() {

    std::string commandinput;
    std::getline(std::cin, commandinput);
    std::vector<std::string> parameters_tokenized = Parser::tokenize(commandinput);

for (size_t j = 0; j < parameters_tokenized.size(); j++) {
       std::cout << parameters_tokenized.at(j)+" ";
   }

    return 0;
}