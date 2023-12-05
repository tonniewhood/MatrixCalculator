
#pragma once

#include <iostream>

struct inputResponse{
    int operation;
    bool hasError;
    std::string errorMsg;
    std::string text;

    inputResponse(int op = -1, bool err = false, std::string errMsg = "Input is empty", std::string t = ""){
        operation = op;
        hasError = err;
        errorMsg = errMsg;
        text = t;
    }

};

struct errorStruct {
    bool hasError;
    std::string errorMsg;
};

inputResponse parseInput(std::string);



