
#include <vector>
#include <iostream>
#include <string>
#include <format>

#include "Matrix.h"
#include "structs.h"

using namespace std;


//Public Methods

Matrix::Matrix(){
    this->numColumns = 0;
    this->numRows = 0;
    this->matrixName = "Empty Matrix";
}

Matrix::Matrix(vector<vector<double>> matrixContents, string label){
    this->matrixArray = matrixContents;
    this->numRows = matrixContents.size();
    this->numColumns = matrixContents.front().size();
    matrixName = label;

    this->allEntriesInts = true;
    this->oneEntryInThousands = false;

    for (int i = 0; i < this->getNumRows(); i++){
        for (int j = 0; j < this->getNumColumns(); j++){

            double entryValue = this->getEntry(i, j);

            if (entryValue > 1000){
                this->oneEntryInThousands = true;
            }

            if (entryValue - (int) entryValue > Matrix::EPSILON){
                this->allEntriesInts = false;
            }

        }

    }

}

void Matrix::print(){

    cout << endl << this->getName() <<  " =\n";

    vector<const char*> printfEntries = this->determinePrintfEntryValue(); 

    for (int i = 0; i < this->getNumRows(); i++){

        for (int j = 0; j < this->getNumColumns() - 1; j++){

            printf(printfEntries.at(0), this->getEntry(i, j));

        }
        printf(printfEntries.at(1), this->getEntry(i, this->getNumColumns() - 1));

    }

    cout << endl;

}

int Matrix::getNumColumns(){
    return this->numColumns;
}

int Matrix::getNumRows(){
    return this->numRows;
}

double Matrix::getEntry(int rowIdx, int columnIdx){
    vector<double> row = this->matrixArray.at(rowIdx);
    double entry = row.at(columnIdx);
    return entry;
}

string Matrix::getName(){
    return this->matrixName;
}

Matrix Matrix::multiply(double scalarOperand){

    vector<vector<double>> newMatrixArray;
    string newMatrixName = this->determineNameForAdding(scalarOperand);

    for (int rowIdx = 0; rowIdx < this->getNumRows(); rowIdx++){


        vector<double> currentRow = this->matrixArray.at(rowIdx);
        vector<double> newRow;

        for (int columnIdx = 0; columnIdx < this->getNumColumns(); columnIdx++){

            double newValue = currentRow.at(columnIdx) * scalarOperand;
            newRow.push_back(newValue);

        }

        newMatrixArray.push_back(newRow);
            
    }

    Matrix newMatrix = Matrix(newMatrixArray, newMatrixName);
    newMatrix.print();
    return newMatrix;

}

Matrix Matrix::multiply(Matrix matrixOperand){

    vector<vector<double>> newMatrixArray;
    string newMatrixName = this->getName() + " * " + matrixOperand.getName();

    if (this->getNumColumns() != matrixOperand.getNumRows()){
        cout << "Error: Matrix dimensions do not match for multiplication." << endl;
        return Matrix();
    }

    for (vector<double> row: this->matrixArray){

        vector<double> newRow;

        for (int columnIdx = 0; columnIdx < matrixOperand.getNumColumns(); columnIdx++){

            double newValue = 0;

            for (int i = 0; i < this->getNumColumns(); i++){

                newValue += row.at(i) * matrixOperand.getEntry(i, columnIdx);

            }

            newRow.push_back(newValue);

        }

        newMatrixArray.push_back(newRow);

    }

    return Matrix(newMatrixArray, newMatrixName);

}

//Private Methods

vector<const char*> Matrix::determinePrintfEntryValue(){

    vector<const char*> printfEntryValue;

    if (oneEntryInThousands){
        printfEntryValue.push_back("\t%.3e");
        printfEntryValue.push_back("\t%.3e\n");

    }
    else if (allEntriesInts) {
        printfEntryValue.push_back("\t%.0f");
        printfEntryValue.push_back("\t%.0f\n");
    }
    else {
        printfEntryValue.push_back("\t%.4f");
        printfEntryValue.push_back("\t%.4f\n");
    }

    return printfEntryValue;

}

string Matrix::determineNameForAdding(double value){

    if (value >= 1000){
        return vformat("{} * {%.3e}", make_format_args(this->getName(), value));
    }
    else if (value - (int) value < Matrix::EPSILON) {
        return vformat("{} * {%.0f}", make_format_args(this->getName(), value));
    }
    else {
        return vformat("{} * {%.4f}", make_format_args(this->getName(), value));
    }

}