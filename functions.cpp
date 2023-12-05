
#include "functions.h"
#include <iostream>

using namespace std;

namespace constants {

    std::string operations[19] = {"Make", "Add", "Sub", "sMultiply", "Multiply", "Inv", "LDU", "QR", "Diag", "SVD", "Span", "Eigen", 
                             "cSpace", "rSpace", "nSpace", "lnSpace", "Transpose", "Disp", "Exit"};

};

/*
This function is made to parse the input from the user and determine if there has been an error in the syntax, and what operation needs to be performed
*/

inputResponse parseInput(string input){

    // If the input was empty, return a default inputResponse to avoid running any operations
    if (input.empty()) {
        return inputResponse();
    }
    else {
        
        // Start by determining the location of the first open parenthasis
        int openIdx = input.find_first_of('(');
        int closeIdx = input.find_last_of(')');
        
        if (openIdx == -1 || closeIdx == -1) {
            return inputResponse(-1, true, "Operation inputs must open and close with parenthasis");
        }

        // Now grab the contents between the parenth
        string operation = input.substr(0, openIdx);
        string text = input.substr(openIdx, closeIdx);

        int operationsLength = (sizeof(constants::operations) / sizeof(*constants::operations));
        bool operationFound = false;
        int operationIndex = 0;

        for (int i = 0; i < operationsLength; i++){
            if (operation.compare(constants::operations[i]) == 0) {
                operationFound = true;
                operationIndex = i;
            }
        }

        if (!operationFound) {
            string errorMsg = "Syntax error in operation. '" + operation + "' is not defined.";
            return inputResponse(-1, true, errorMsg);
        }
        else {
            return inputResponse(operationIndex, false, "", text);
        }

    }

}
