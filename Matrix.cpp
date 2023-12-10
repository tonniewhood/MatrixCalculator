
#include <vector>

using namespace std;

class Matrix {

    private : 
        int numRows;
        int numColumns;
        vector<vector<double>> matrixArray;

    public : 
        Matrix(vector<vector<double>> matrixContents){
            this->matrixArray = matrixContents;
            this->numRows = matrixContents.size();
            this->numColumns = matrixContents.front().size();
        };

};