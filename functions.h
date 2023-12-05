
#pragma once

#include <iostream>

struct inputResponse{
    int operation;
    bool hasError;
    std::string errorMsg;
    std::string text;
};

inputResponse parseInput(std::string);



