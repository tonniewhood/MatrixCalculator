
#pragma once

class Matrix {

    public:
        /* Data */


        /* Methods */
        Matrix();
        Matrix(std::vector<std::vector<double>> matrixArray, std::string name);

        void print();

        int getNumColumns();
        int getNumRows();

        double getEntry(int rowIdx, int columnIdx);

        std::string getName();
        

    private:
        /* Data */
        bool allEntriesInts;
        bool oneEntryInThousands;

        int numColumns;
        int numRows;

        double EPSILON = 1.0E-14;

        std::string matrixName;

        std::vector<std::vector<double>> matrixArray;


        /* Methods */ 
        std::vector<const char*> determinePrintfEntryValue();

};