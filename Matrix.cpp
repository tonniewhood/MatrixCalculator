
#include <vector>
#include <iostream>
#include <string>
#include "test.h"

using namespace std;

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

int Matrix::getNumRows(){
    return this->numRows;
}

int Matrix::getNumColumns(){
    return this->numColumns;
}

double Matrix::getEntry(int rowIdx, int columnIdx){
    vector<double> row = this->matrixArray.at(rowIdx);
    double entry = row.at(columnIdx);
    return entry;
}

string Matrix::getName(){
    return this->matrixName;
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