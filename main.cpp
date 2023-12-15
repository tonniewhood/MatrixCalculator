
#include <iostream>

#include "structs.h"
#include "CalculatorInstance.h"
#include "Matrix.h"

using namespace std;

int main() {

    bool done = false;

    while (!done){

        CalculatorInstance instance = CalculatorInstance();

        cout << ">> ";

        char* inputBuffer;
        cin.getline(inputBuffer, 512);

        string input;
        input = inputBuffer;

        inputResponse response = instance.parseInput(input);

        // Determine if there was a syntax error in the use input, if so, tell the user and request a second input
        if(response.hasError){
            cout << response.errorMsg << "\n\n";
            continue;
        }
        else {
            done = instance.perform_operation(response);
        }

    }

    return 0;

}

