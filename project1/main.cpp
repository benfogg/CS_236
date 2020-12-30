
#include "scanner.h"

int main (int argc, char* argv[]) {
    if (!argv[1]) {
        cout << "must include file name in commandline" << endl;
        cout << "Total Tokens = 0" << endl;
    }
    else {
        string filename = argv[1];
        Scanner myScanner(filename);  
        myScanner.tokenize();

        for ( unsigned int i = 0; i < myScanner.tokenList.size(); i++) {
            cout << myScanner.tokenList.at(i).toString() << endl;
        }
        cout << "Total Tokens = " << myScanner.tokenList.size() << endl;
    }
    return 0;
}