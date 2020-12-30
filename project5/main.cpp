#include "scanner.h"
#include "parser.h"
#include "interpreter.h"

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
        Interpreter myInterpreter;
        bool trueorfalse = myParser.DatalogProgram(myScanner.GetList());
        if (trueorfalse == false) {
            //myParser.ToString();
            myInterpreter.SetDatalog(myParser.GetDatalog());
            //cout << myInterpreter.ToString();
        }
    }
    return 0;
}