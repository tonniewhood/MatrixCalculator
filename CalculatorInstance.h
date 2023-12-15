
#pragma once

class CalculatorInstance {

    private:

        /* Data */
        string operations[19] = {"Make", "Add", "Sub", "sMultiply", "Multiply", "Inv", "LDU", "QR", "Diag", "SVD", "Span", "Eigen", 
                                "cSpace", "rSpace", "nSpace", "lnSpace", "Transpose", "Disp", "Exit"};

        vector<Matrix> matrixList;
        vector<scalarEntry> scalarList;


        /* Methods */
        void addOperation(string input);
        void displayInitializingError(int errorType);
        void initializeVariable(string inputText);
        void performAddition(vector<operand> values);

        bool areOperandTypesSame(vector<operand> values);

        int findInMatrixList(string element);
        int findInScalarList(string element);

        string findRemaining(string inputString);
        
        vector<operand> findOperands(string input);
        
        matrixResponse addMatrices(Matrix matrix1, Matrix matrix2);
        matrixResponse parseForMatrix(string matrixContents, string matrixName);
        
        rowResponse stringRowToDouble(string rowString);
        
        
    public:

        CalculatorInstance();

        bool perform_operation(inputResponse input);

        inputResponse parseInput(string input);
        

};