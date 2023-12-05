
#include "functions.h"
#include <iostream>

using namespace std;

int main() {

    bool done = false;

    while (!done){

        string input;
        cout << ">>";
        cin >> input;

        string operation = parse_input(input);

    }

    return 0;

}

