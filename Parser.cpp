#include <iostream>
#include "Parser.h"

std::vector<std::string> Parser::tokenize(const std::string& input) {
    std::vector<std::string> parameters;
    std::string current_parameter;
    for(int i = 0; i < input.size(); i++ ) {
        if (input[i] == ' ' || input[i] == '(' || input[i] == ')' || input[i] == ',') {
            parameters.push_back(current_parameter);
            if (input[i] != ' ') { parameters.push_back(std::string(1,input[i])); } // Store ,() but not spaces

            current_parameter = "";

        } else {
            current_parameter += input[i];
        }
    }
    if (!current_parameter.empty()) {
        parameters.push_back(current_parameter);
        current_parameter = "";
    }
    
  return parameters;
}