
#include "functions.h"
#include <iostream>

using namespace std;

int main() {

    bool done = false;

    while (!done){

        string input;
        cout << ">>";
        cin >> input;

        inputResponse response = parseInput(input);

        // Determine if there was a syntax error in the use input, if so, tell the user and request a second input
        if(response.hasError){
            cout << response.errorMsg << "\n\n";
            continue;
        }
        else {
            // Perform the operation that corresponds with the operations.txt file
            switch (response.operation){
                // Initialize a matrix
                case (0) : {
                    
                }
                case (1) : {

                }
                case (2) : {

                }
                case (3) : {

                }
                case (4) : {

                }
                case (5) : {

                }
                case (6) : {
                    
                }
                case (7) : {
                    
                }
                case (8) : {
                    
                }
                case (9) : {
                    
                }
                case (10) : {
                    
                }
                case (11) : {
                    
                }
                case (12) : {
                    
                }
                case (13) : {
                    
                }
                case (14) : {
                    
                }
                case (15) : {
                    
                }
                case (16) : {
                    
                }
                case (17) : {
                    
                }
                case (18) : {
                    done = true;
                    continue;
                }
                default : {
                    cout << "Error. Operation could not be found\n" << endl; 
                }
            }
        }

    }

    return 0;

}

