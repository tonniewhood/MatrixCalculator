
#include "structs.h"
#include "Matrix.cpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class CalculatorInstance {

    private:

        /* data */
        string operations[19] = {"Make", "Add", "Sub", "sMultiply", "Multiply", "Inv", "LDU", "QR", "Diag", "SVD", "Span", "Eigen", 
                                "cSpace", "rSpace", "nSpace", "lnSpace", "Transpose", "Disp", "Exit"};

        vector<scalarEntry> scalarList;
        vector<matrixEntry> matrixList;

        /* methods */
        
        /*
        This method is designed to find the remaining text of an input by finding the first comma, and trimming everything before it and any whitespace trailing it
        */
        string findRemaining(string inputString){

            int firstCommaIndex = inputString.find_first_of(',');
            string outputString = inputString.substr(firstCommaIndex + 1, string::npos);
            return outputString = outputString.substr(outputString.find_first_not_of(' '), string::npos);

        }

        /*
        This method is designed to take the input for a user that is designed for a matrix, and return a list of the rows in the matrix
        */
        parsedMatrix parseForMatrix(string matrixContents){

            vector<vector<double>> matrix;

            // First check to make sure the first character is an open square braket, and that the last is a closed square bracket
            bool enclosedInSquareBrakets = (matrixContents.front() == '[') && (matrixContents.back() == ']');
            if (!enclosedInSquareBrakets){
                vector<vector<double>> blank;
                parsedMatrix improperSqureBrakets = {blank, true, 1};
                return improperSqureBrakets;
            }

            matrixContents = matrixContents.substr(1, string::npos);
            int rowSize = -1;

            // Each itteration grab the next row and convert it into a vector of doubles
            while(!matrixContents.empty()){

                int firstSemiColonIndex = matrixContents.find_first_of(';');
                string rowString = matrixContents.substr(0, firstSemiColonIndex + 1);
                parsedRow rowList = stringRowToDouble(rowString);

                if (rowList.hasError){
                    vector<vector<double>> blank;
                    parsedMatrix rowArgumentsIncorrect = {blank, true, 2};
                    return rowArgumentsIncorrect;
                }

                matrix.push_back(rowList.rowContents);
                matrixContents = matrixContents.substr(0, firstSemiColonIndex + 1);

            }

            parsedMatrix correctlyParsedMatrix = {matrix, false, -1};

        }

        /*
        This method takes in a string and converts it into a vector of doubles
        */
        parsedRow stringRowToDouble(string rowString){

            parsedRow rowInDoubles;

            while (!rowString.empty()){

                int firstCommaIndex = rowString.find_first_of(',');
                string currentValue = rowString.substr(0, firstCommaIndex + 1);
                double convertedValue;

                // Try to convert the current entry into a double, if it doesn't work, return an empty vector to signal that there was an error
                try {
                    convertedValue = stod(currentValue);
                }
                catch (const invalid_argument& e){
                    vector<double> blank;
                    parsedRow improperArguments = {blank, true};
                    return improperArguments;
                }

                rowInDoubles.rowContents.push_back(convertedValue);
                rowString = rowString.substr(firstCommaIndex + 1, string::npos);

            }

            return rowInDoubles;

        }

        /*
        This method takes the error that was found and prints it to the console
        */
        void displayInitializingError(int errorType){

            switch (errorType) {

                case 0 : {
                    cout << "Rows must all be of the same size" << endl;
                    return;
                }
                case 1 : {
                    cout << "Matrix contents must start and end with square brakets" << endl;
                    return;
                }
                case 2 : {
                    cout << "Rows must have values that can convert into doubles and be seperated by commas;" << endl;
                    return;
                }
                default : {
                    cout << "Untracked error" << endl;
                    return;
                }

            }

        }

        /*
        This method is designed to initialize a matrix and then append it to the list of matrices
        */
        void InitializeVariable(string inputText){

            // First determine if the varaible is a matrix or scalar, then find it's label
            int firstCommaIndex = inputText.find_first_of(',');
            string varType = inputText.substr(0, firstCommaIndex + 1);
            transform(varType.cbegin(), varType.cend(), varType.begin(), [](char c){ return tolower(c); });
            string remainingInput = CalculatorInstance::findRemaining(inputText);

            firstCommaIndex = remainingInput.find_first_of(',');
            string varLabel = remainingInput.substr(0, firstCommaIndex + 1);
            remainingInput = CalculatorInstance::findRemaining(remainingInput);

            // If the variable is not listed as a matrix or a scalar, inform the user and don't move forward with variable creation
            if (varType.compare("matrix") != 0) {

                parsedMatrix matrix = parseForMatrix(remainingInput);
                if (matrix.hasError) {
                    displayInitializingError(matrix.errorType);
                }
                else {
                    matrixEntry matrixToPush = {matrix.matrixContents, varLabel};
                    matrixList.push_back(matrixToPush);
                }

            }
            else if (varType.compare("scalar") == 0){

                // First create a new entry for the scalar, then add it to the rest of the list
                try {
                    double newValue = stod(remainingInput);
                    scalarEntry newVar = {newValue, varLabel};
                    scalarList.push_back(newVar);
                }
                catch (const invalid_argument& e){
                    cout << "Value '" << remainingInput << "' could not be converted to a double" << endl;
                }

            }
            else {
                cout << "Variable must be of type 'matrix' or 'scalar'" << endl;
            }

        }


    public:

    /*
    Default constructor for a calculator instance
    */
    CalculatorInstance(){

    }

        /*
        This method is made to parse the input from the user and determine if there has been an error in the syntax, and what operation needs to be performed
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

                // Now grab the contents between the parenthesis to put as the text, and everything before as the operation
                string operation = input.substr(0, openIdx);
                string text = input.substr(openIdx, closeIdx);

                // Now determine the size of the operations array, and index through it to see if the given operation matches one of the current supported operations
                int operationsLength = (sizeof(CalculatorInstance::operations) / sizeof(*CalculatorInstance::operations));
                bool operationFound = false;
                int operationIndex = 0;

                for (int i = 0; i < operationsLength; i++){
                    if (operation.compare(CalculatorInstance::operations[i]) == 0) {
                        operationFound = true;
                        operationIndex = i;
                    }
                }

                // If the operation isn't found, return a respone indicating that, and that there was an error, otherwise return what the operation is, and the contents for the operation
                if (!operationFound) {
                    string errorMsg = "Syntax error in operation. '" + operation + "' is not defined.";
                    return inputResponse(-1, true, errorMsg);
                }
                else {
                    return inputResponse(operationIndex, false, "", text);
                }

            }

        }

        /*
        This method is designed to take the response from the user and perform the correct operation on the given matrix
        */
        bool perform_operation(inputResponse input){
                        // Perform the operation that corresponds with the operations.txt file
                    switch (input.operation){
                        // Handle an empty response
                        case (-1) : {
                            cout << endl;
                            return false;
                        }
                        // Initialize a matrix
                        case (0) : {
                            cout << "Initialization not yet implemented\n" << endl;
                            return false;
                        }
                        // Perform addition
                        case (1) : {
                            cout << "Addition not yet implemented\n" << endl;
                            return false;
                        }
                        // Perform subtraction
                        case (2) : {
                            cout << "Subtraction not yet implemented\n" << endl;
                            return false;
                        }
                        case (3) : {
                            cout << "Scalar Multiplication not yet implemented\n" << endl;
                            return false;
                        }
                        case (4) : {
                            cout << "Matrix/Vector Multiplcation not yet implemented\n" << endl;
                            return false;
                        }
                        case (5) : {
                            cout << "Inverses not yet implemented\n" << endl;
                            return false;
                        }
                        case (6) : {
                            cout << "LDU Decomposition not yet implemented\n" << endl;
                            return false;
                        }
                        case (7) : {
                            cout << "QR Factorization not yet implemented\n" << endl;
                            return false;
                        }
                        case (8) : {
                            cout << "Diagonalization not yet implemented\n" << endl;
                            return false;
                        }
                        case (9) : {
                            cout << "SVD Decomposition not yet implemented\n" << endl;
                            return false;
                        }
                        case (10) : {
                            cout << "Span not yet implemented\n" << endl;
                            return false;
                        }
                        case (11) : {
                            cout << "Eigenvalues and Eigenvectors not yet implemented\n" << endl;
                            return false;
                        }
                        case (12) : {
                            cout << "Column Space not yet implemented\n" << endl;
                            return false;
                        }
                        case (13) : {
                            cout << "Row Space not yet implemented\n" << endl;
                            return false;
                        }
                        case (14) : {
                            cout << "Null Space not yet implemented\n" << endl;
                            return false;
                        }
                        case (15) : {
                            cout << "Left Null Space not yet implemented\n" << endl;
                            return false;
                        }
                        case (16) : {
                            cout << "Transposition not yet implemented\n" << endl;
                            return false;
                        }
                        case (17) : {
                            cout << "Displaying not yet implemented\n" << endl;
                            return false;
                        }
                        case (18) : {
                            return true;
                        }
                        default : {
                            cout << "Error. Operation could not be found\n" << endl;
                            return false; 
                        }
                    }
        }

};