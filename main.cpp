
#include "functions.h"
#include <iostream>

using namespace std;

int main() {

    bool done = false;

    while (!done){

        cout << ">> ";

        char* inputBuffer;
        cin.getline(inputBuffer, 512);

        string input;
        input = inputBuffer;

        inputResponse response = parseInput(input);

        // Determine if there was a syntax error in the use input, if so, tell the user and request a second input
        if(response.hasError){
            cout << response.errorMsg << "\n\n";
            continue;
        }
        else {
            // Perform the operation that corresponds with the operations.txt file
            switch (response.operation){
                // Handle an empty response
                case (-1) : {
                    cout << endl;
                    break;
                }
                // Initialize a matrix
                case (0) : {
                    cout << "Initialization not yet implemented\n" << endl;
                    break;
                }
                // Perform addition
                case (1) : {
                    cout << "Addition not yet implemented\n" << endl;
                    break;
                }
                // Perform subtraction
                case (2) : {
                    cout << "Subtraction not yet implemented\n" << endl;
                    break;
                }
                case (3) : {
                    cout << "Scalar Multiplication not yet implemented\n" << endl;
                    break;
                }
                case (4) : {
                    cout << "Matrix/Vector Multiplcation not yet implemented\n" << endl;
                    break;
                }
                case (5) : {
                    cout << "Inverses not yet implemented\n" << endl;
                    break;
                }
                case (6) : {
                    cout << "LDU Decomposition not yet implemented\n" << endl;
                    break;
                }
                case (7) : {
                    cout << "QR Factorization not yet implemented\n" << endl;
                    break;
                }
                case (8) : {
                    cout << "Diagonalization not yet implemented\n" << endl;
                    break;
                }
                case (9) : {
                    cout << "SVD Decomposition not yet implemented\n" << endl;
                    break;
                }
                case (10) : {
                    cout << "Span not yet implemented\n" << endl;
                    break;
                }
                case (11) : {
                    cout << "Eigenvalues and Eigenvectors not yet implemented\n" << endl;
                    break;
                }
                case (12) : {
                    cout << "Column Space not yet implemented\n" << endl;
                    break;
                }
                case (13) : {
                    cout << "Row Space not yet implemented\n" << endl;
                    break;
                }
                case (14) : {
                    cout << "Null Space not yet implemented\n" << endl;
                    break;
                }
                case (15) : {
                    cout << "Left Null Space not yet implemented\n" << endl;
                    break;
                }
                case (16) : {
                    cout << "Transposition not yet implemented\n" << endl;
                    break;
                }
                case (17) : {
                    cout << "Displaying not yet implemented\n" << endl;
                    break;
                }
                case (18) : {
                    done = true;
                    break;
                }
                default : {
                    cout << "Error. Operation could not be found\n" << endl;
                    break; 
                }
            }
        }

    }

    return 0;

}

