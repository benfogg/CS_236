#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, 
    MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFa, ERROR
};

class Token {
     public:
        Token();
        ~Token();
        string toString();
        string TypeString();
        string GetValue();
        TokenType GetType();
        int GetLineNumber();
        void SetValues(string token, int lineNumber);
        void SetComplexValues(string type, string token, int lineNumber);
    protected:
        string tokenValue;
        int lineNumber;
        TokenType tokenType;
};