
#pragma once

#include <iostream>

// This is the parsed response from the user containing the operation, if there is an error, what the error message is, and the contents for the desired entry
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

// This is an entry for the linked list containing each scalar variable the user adds
struct scalarEntry {
    double value;
    std::string label;
    scalarEntry* nextScalarEntry;
};

// This is an entry for the linked list containing each scalar variable the user adds
struct matrixEntry {
    Matrix matrix;
    std::string label;
    matrixEntry* nextMatrixEntry;
};

