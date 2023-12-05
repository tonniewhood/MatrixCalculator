
class Matrix {

    private : 
        int numRows;
        int numColumns;
        double** matrixArray;

    public : 
        Matrix(double** matrix_input, int numRows, int numColumns){
            this->matrixArray = matrix_input;
            this->numColumns = numColumns;
            this->numRows = numRows;
        };

};