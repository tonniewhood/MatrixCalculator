

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>

#include "structs.h"
#include "CalculatorInstance.h"
#include "Matrix.h"

using namespace std;

// Private Methods

void CalculatorInstance::addOperation(string input){

    vector<operand> values;

    try {
        values = findOperands(input);
    }
    catch (const invalid_argument& e){
        cout << e.what() << endl;
        return;
    }
    

    if(values.size() > 2){
        cout << "Addition can only be performed on two operands" << endl;
        return;
    }

    bool typesSame = areOperandTypesSame(values);

    if (!typesSame){
        cout << "Operands must be of the same type (cannot add a matrix to a scalar)" << endl;
        return;
    }

    performAddition(values);

}

void CalculatorInstance::displayInitializingError(int errorType){

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

void CalculatorInstance::initializeVariable(string inputText){

    int firstCommaIndex = inputText.find_first_of(',');
    string varType = inputText.substr(0, firstCommaIndex + 1);
    transform(varType.cbegin(), varType.cend(), varType.begin(), [](char c){ return tolower(c); });
    string remainingInput = CalculatorInstance::findRemaining(inputText);

    firstCommaIndex = remainingInput.find_first_of(',');
    string varLabel = remainingInput.substr(0, firstCommaIndex + 1);
    remainingInput = CalculatorInstance::findRemaining(remainingInput);

    if (varType.compare("matrix") == 0) {

        matrixResponse matrix = parseForMatrix(remainingInput, varLabel);
        if (matrix.hasError) {
            displayInitializingError(matrix.errorType);
        }
        else {
            matrixList.push_back(matrix.matrix);
        }

    }
    else if (varType.compare("scalar") == 0){

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

void CalculatorInstance::performAddition(vector<operand> values){

    

}

bool CalculatorInstance::areOperandTypesSame(vector<operand> values){

    operand operand1 = values.at(0);
    operand operand2 = values.at(1);

    if (operand1.isMatrix){
        return operand2.isMatrix;
    }
    else {
        return operand2.isScalar;
    }

}

int CalculatorInstance::findInMatrixList(string element){

    for (int i = 0; i < this->matrixList.size(); i++){

        Matrix currentElement = this->matrixList.at(i);
        bool labelIsFound = currentElement.getName().compare(element) == 0;
        if (labelIsFound) {
            return i;
        }

    }

    return -1;

}

int CalculatorInstance::findInScalarList(string element){

    for (int i = 0; i < this->scalarList.size(); i++){

        scalarEntry currentElement = this->scalarList.at(i);
        bool labelIsFound = currentElement.label.compare(element) == 0;
        if (labelIsFound) {
            return i;
        }

    }

    return -1;

}

string CalculatorInstance::findRemaining(string inputString){

    int firstCommaIndex = inputString.find_first_of(',');
    string outputString = inputString.substr(firstCommaIndex + 1, string::npos);
    return outputString = outputString.substr(outputString.find_first_not_of(' '), string::npos);

}

vector<operand> CalculatorInstance::findOperands(string input) {

    vector<operand> values;

    while (!input.empty()){

        int firstCommaIndex = input.find_first_of(',');
        string element = input.substr(0, firstCommaIndex + 1);

        int indexInMatrixList = findInMatrixList(element);

        if (indexInMatrixList != -1){
            operand newOperand = {this->matrixList.at(indexInMatrixList).getName(), true, false};
            values.push_back(newOperand);
            input = findRemaining(input);
            continue;
        }

        int indexInScalarList = findInScalarList(element);

        if (indexInScalarList != -1){
            operand newOperand = {this->scalarList.at(indexInScalarList).label, true, false};
            values.push_back(newOperand);
            input = findRemaining(input);
            continue;
        }

        try {
            stod(element);
        }
        catch (const invalid_argument& e){
            throw invalid_argument(" if an element is not a variable name it must be able to be cast to double");
        }

    }

    return values;

}

matrixResponse CalculatorInstance::addMatrices(Matrix matrix1, Matrix matrix2){

    bool bothRowSizesSame = matrix1.getNumRows() == matrix2.getNumRows();
    bool bothColumnSizesSame = matrix1.getNumColumns() == matrix2.getNumColumns();

    if (!bothColumnSizesSame || !bothRowSizesSame){
        matrixResponse sizesNotSame = {Matrix(), true, 3};
        return sizesNotSame;
    }

    vector<vector<double>> newMatrixArray;

    for (int i = 0; i < matrix1.getNumRows(); i++){

        vector<double> newRow;

        for (int j = 0; i < matrix1.getNumColumns(); j++){

            double newValue = matrix1.getEntry(i, j) + matrix2.getEntry(i, j);
            newRow.push_back(newValue);

        }

        newMatrixArray.push_back(newRow);

    }

    string newName = matrix1.getName() + " + " + matrix2.getName();
    matrixResponse newMatrix = {Matrix(newMatrixArray, newName), false, -1};
    return newMatrix;

}

matrixResponse CalculatorInstance::parseForMatrix(string matrixContents, string matrixName){

    vector<vector<double>> matrixArray;

    bool enclosedInSquareBrakets = (matrixContents.front() == '[') && (matrixContents.back() == ']');
    if (!enclosedInSquareBrakets){
        matrixResponse improperSqureBrakets = {Matrix(), true, 1};
        return improperSqureBrakets;
    }

    matrixContents = matrixContents.substr(1, string::npos);
    int rowSize = -1;

    while(!matrixContents.empty()){

        int firstSemiColonIndex = matrixContents.find_first_of(';');
        string rowString = matrixContents.substr(0, firstSemiColonIndex + 1);
        rowResponse rowList = stringRowToDouble(rowString);

        if (rowList.hasError){
            matrixResponse rowArgumentsIncorrect = {Matrix(), true, 2};
            return rowArgumentsIncorrect;
        }

        if (rowSize == -1){
            rowSize = rowList.rowContents.size();
        }
        else if (rowSize != rowList.rowContents.size()){
            matrixResponse rowSizesDontMatch = {Matrix(), true, 0};
            return rowSizesDontMatch;
        }

        matrixArray.push_back(rowList.rowContents);
        matrixContents = matrixContents.substr(0, firstSemiColonIndex + 1);

    }

    Matrix newMatrix = Matrix(matrixArray, matrixName);
    matrixResponse correctlyParsedMatrix = {newMatrix, false, -1};

}

rowResponse CalculatorInstance::stringRowToDouble(string rowString){

    rowResponse rowInDoubles;

    while (!rowString.empty()){

        int firstCommaIndex = rowString.find_first_of(',');
        string currentValue = rowString.substr(0, firstCommaIndex + 1);
        double convertedValue;

        try{
            convertedValue = stod(currentValue);
        }
        catch (const invalid_argument& e){
            vector<double> blank;
            rowResponse improperArguments = {blank, true};
            return improperArguments;
        }

        rowInDoubles.rowContents.push_back(convertedValue);
        rowString = rowString.substr(firstCommaIndex + 1, string::npos);

    }

    return rowInDoubles;

}


// Public Methods

CalculatorInstance::CalculatorInstance(){

}

bool CalculatorInstance::perform_operation(inputResponse input){
                
    switch (input.operation){
        // Handle an empty response
        case (-1) : {
            cout << endl;
            return false;
        }
        // Initialize a matrix
        case (0) : {
            initializeVariable(input.text);
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

inputResponse CalculatorInstance::parseInput(string input){

    if (input.empty()) {
        return inputResponse();
    }
    else {
        
        int openParenthesisIdx = input.find_first_of('(');
        int closeParenthesisIdx = input.find_last_of(')');
        
        if (openParenthesisIdx == string::npos || (closeParenthesisIdx == string::npos && input.back() != ')')) {
            return inputResponse(-1, true, "Operation inputs must open and close with parenthasis");
        }

        string operation = input.substr(0, openParenthesisIdx);
        int substrLength = closeParenthesisIdx - openParenthesisIdx;
        string text = input.substr(openParenthesisIdx + 1, substrLength);

        int operationsArrayLength = (sizeof(CalculatorInstance::operations) / sizeof(*CalculatorInstance::operations));
        bool operationFound = false;
        int operationIndex = 0;

        for (int i = 0; i < operationsArrayLength; i++){
            if (operation.compare(CalculatorInstance::operations[i]) == 0) {
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
