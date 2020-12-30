#pragma once
#include "token.h"
#include <fstream>
#include <queue>

enum state {init, sChar, sSpecial, sFinal, sEOF, sID, sComment, sString, sWhiteSpace};

class Scanner {
    public:
        // Functions
        Scanner(string nameOfFile);
        ~Scanner();
        void tokenize();
        queue <Token> GetList();

        //variables
        queue <Token> tokenList;
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
        //int initial;
};


