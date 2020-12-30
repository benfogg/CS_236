#include "token.h"

Token::Token() {
    tokenValue = "BEN FOGG";
    lineNumber = -1;
    tokenType = ERROR;
}

Token::~Token() {
}

int Token::GetLineNumber(){
    return lineNumber;
}

TokenType Token::GetType() {
    return tokenType;
}

string Token::toString() {
    string theToken;
    string type = "ERROR1";
    switch (tokenType) {
        case COMMA:
            type = "COMMA";
            break;
        case PERIOD:
            type = "PERIOD";
            break;
        case Q_MARK:
            type = "Q_MARK";
            break;
        case LEFT_PAREN:
            type = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            type = "RIGHT_PAREN";
            break;
        case COLON:
            type = "COLON";
            break;
        case COLON_DASH:
            type = "COLON_DASH";
            break;
        case MULTIPLY:
            type = "MULTIPLY";
            break;
        case ADD: 
            type = "ADD";
            break;
        case SCHEMES:
            type = "SCHEMES";
            break;
        case FACTS:
            type = "FACTS";
            break;
        case RULES:
            type = "RULES";
            break;
        case QUERIES:
            type = "QUERIES";
            break;
        case ID:
            type = "ID";
            break;
        case STRING:
            type = "STRING";
            break;
        case COMMENT:
            type = "COMMENT";
            break;
        case UNDEFINED:
            type = "UNDEFINED";
            break;
        case EOFa:
            type = "EOF";
            break;
        case ERROR:
            type = "ERROR";
    }
    theToken = "(" + type + ",\"" + tokenValue + "\"," + to_string(lineNumber) + ")";
    return theToken;
}

void Token::SetValues(string myString ,int lineNum) {
        lineNumber = lineNum;
        tokenValue = myString;
    if (myString == ",") {
        tokenType = COMMA;
    }
    else if (myString == ".") {
        tokenType = PERIOD;
    }
    else if (myString == "?") {
        tokenType = Q_MARK;
    }
    else if (myString == "(") {
        tokenType = LEFT_PAREN;
    }
    else if (myString == ")") {
        tokenType = RIGHT_PAREN;
    }
    else if (myString == ":-") {
        tokenType = COLON_DASH;
    }
    else if (myString == ":") {
        tokenType = COLON;
    }
    else if (myString == "*") {
        tokenType = MULTIPLY;
    }
    else if (myString == "+") {
        tokenType = ADD;
    }
    else if (myString == "Schemes") {
        tokenType = SCHEMES;
    }
    else if (myString == "Facts") {
        tokenType = FACTS;
    }
    else if (myString == "Queries") {
        tokenType = QUERIES;
    }
    else if (myString == "Rules") {
        tokenType = RULES;
    }
    else if (myString == "EOF") {
        tokenType = EOFa;
        tokenValue = "";
    }
    //NEED TO ADD STRINGS AND COMMENTS and IDs
    else {
        tokenType = UNDEFINED;
    }

}

void Token::SetComplexValues (string type, string token, int lineNum) {
    if (type == "ID") {
        tokenType = ID;
        tokenValue = token;
        lineNumber = lineNum;
    }
    else if ( type == "COMMENT") {
        tokenType = COMMENT;
        tokenValue = token; // may need to be modified
        lineNumber = lineNum;
    }
    else if (type == "STRING") {
        tokenType = STRING;
        tokenValue = token; // may need ot be modified
        lineNumber = lineNum;

    }
    else if (type == "UNDEFINED") {
        tokenType = UNDEFINED;
        tokenValue = token; // may need to be modified
        lineNumber = lineNum;

    }
}

string Token::TypeString() {
    string type = "ERROR1";
    switch (tokenType) {
        case COMMA:
            type = "COMMA";
            break;
        case PERIOD:
            type = "PERIOD";
            break;
        case Q_MARK:
            type = "Q_MARK";
            break;
        case LEFT_PAREN:
            type = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            type = "RIGHT_PAREN";
            break;
        case COLON:
            type = "COLON";
            break;
        case COLON_DASH:
            type = "COLON_DASH";
            break;
        case MULTIPLY:
            type = "MULTIPLY";
            break;
        case ADD: 
            type = "ADD";
            break;
        case SCHEMES:
            type = "SCHEMES";
            break;
        case FACTS:
            type = "FACTS";
            break;
        case RULES:
            type = "RULES";
            break;
        case QUERIES:
            type = "QUERIES";
            break;
        case ID:
            type = "ID";
            break;
        case STRING:
            type = "STRING";
            break;
        case COMMENT:
            type = "COMMENT";
            break;
        case UNDEFINED:
            type = "UNDEFINED";
            break;
        case EOFa:
            type = "EOF";
            break;
        case ERROR:
            type = "ERROR";
        break;
    }
    return type;
}

string Token::GetValue() {
    return tokenValue;
}