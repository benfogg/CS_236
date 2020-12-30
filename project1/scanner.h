#pragma once
#include "token.h"
#include <map>
#include <fstream>
#include <vector>

enum state {init, sChar, sSpecial, sFinal, sEOF, sID, sComment, sString, sWhiteSpace};

class Scanner {
    public:
        // Functions
        Scanner(string nameOfFile);
        ~Scanner();
        void tokenize();

        //variables
        vector <Token> tokenList;
    protected:
        //functions
        Token StateMachine();
        int LineGenerator();
        string WordExtractor();
        bool IsWhiteSpace();

        //variables
        ifstream file;
        string fileName;
        char currentChar;
        char nextChar;
        int currentLine;
        state currentstate;
        string facts;
        bool nextCharVal;
        int initial;
};


