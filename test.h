
#pragma once

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

// This is an entry for the vector containing each scalar variable the user adds
struct scalarEntry {
    double value;
    std::string label;
};

// This is a struct that is designed to indicate of there was an error parsing the matrix. It contains both the actual matrix, and an error variable
struct matrixResponse {
    Matrix matrix;
    bool hasError;
    int errorType;
};

// This struct is similar to the parsedMatrix one, but just handles an individual row
struct rowResponse {
    std::vector<double> rowContents;
    bool hasError;
};

struct operand {
    std::string label;
    bool isMatrix;
    bool isScalar;
};
