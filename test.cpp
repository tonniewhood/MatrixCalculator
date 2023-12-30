
#include <iostream>
#include <vector>

// #include "structs.h"
// #include "CalculatorInstance.h"
#include "Matrix.h"

using namespace std;

int main(){

    // CalculatorInstance instance;

    vector<vector<double>> matrixArray = {
        {1, 5},
        {3, 2}
    };

    // for (int i = 0; i < 5; i++){
    //     int modifier = i + 1;
    //     vector<double> row;
    //     for (int j = 1; j < 6; j++) {
    //         row.push_back(j * modifier);
    //     }
    //     matrixArray.push_back(row);
    // }

    Matrix testMatrixA = Matrix(matrixArray, "A");
    // Matrix testMatrixB = Matrix(matrixArray, "B");
    
    testMatrixA.print();
    Matrix Asquared = testMatrixA.multiply(testMatrixA);
    Asquared.print();


    return 0;

}

