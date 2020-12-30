#include "scanner.h"
#include "parser.h"

int main (int argc, char* argv[]) {
    if (!argv[1]) {
        cout << "must include file name in commandline" << endl;
        cout << "Total Tokens = 0" << endl;
    }
    else {
        string filename = argv[1];
        Scanner myScanner(filename);  
        myScanner.tokenize();
        Parser myParser;
        bool trueorfalse = myParser.DatalogProgram(myScanner.GetList());
        if (trueorfalse == false) {
            myParser.ToString();
        }
    }
    return 0;
}