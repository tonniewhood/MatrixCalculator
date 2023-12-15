
#include <iostream>
#include <vector>

#include "structs.h"
#include "CalculatorInstance.h"
#include "Matrix.h"

using namespace std;

int main(){

    CalculatorInstance instance;

    vector<vector<double>> matrixArray;

    for (int i = 0; i < 5; i++){
        int modifier = i + 1;
        vector<double> row;
        for (int j = 0; j < 5; j++) {
            row.push_back((double) ((j + 1000) * modifier));
        }
        matrixArray.push_back(row);
    }

    Matrix testMatrixA = Matrix(matrixArray, "A");
    Matrix testMatrixB = Matrix(matrixArray, "B");



    return 0;

}

