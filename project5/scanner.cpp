#include "scanner.h"
#include "token.h"
#include <fstream>
#include <cctype>
#include <cstdio> 
#include <sstream> 
// it is having trouble with the initial condition compiling them more than once

Scanner::Scanner(string nameOfFile) {
    fileName = nameOfFile;
    currentChar = '=';
    nextChar = '=';
    currentLine = 1;
    currentstate = init;
    file.open(fileName);
    facts = "==";
    //initial = 1;
}

Scanner::~Scanner() {
    file.close();
}

bool Scanner::IsWhiteSpace() {
    if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n' || currentChar == '\r') {
        return true;
    }
    else {
        return false;
    }
}


string Scanner::WordExtractor() {
    string newWord;
    char wordChar;
    newWord += currentChar;  
    wordChar = file.get();
    while(isalpha(wordChar)||isdigit(wordChar)) {
        newWord = newWord + wordChar;
        wordChar = file.get();  
    }
    if (!(isalpha(wordChar)) && !isdigit(wordChar)) {
        nextCharVal = true;
        nextChar = wordChar;
    }            
    return newWord;
}

int Scanner::LineGenerator() {
    currentLine++;
    return currentLine;
}

void Scanner::tokenize() {
    while (file.good()) {
        Token newToken;
        if (nextCharVal == true) {
            currentChar = nextChar;
            nextCharVal = false;
        }
        else {
            currentChar = file.get();
        }
        newToken = StateMachine();
        if /*(*/(!(IsWhiteSpace()) /*&& initial == 0)*/) { // change to newline and stuff that doesn't make a token
            if (newToken.GetType() == COMMENT) {
                //cout << "Comment Ignored" << endl;
            }
            else {
                tokenList.push(newToken);
            }
        }
        else if (currentChar == EOF) {
            tokenList.push(newToken);
        }
        //initial = 0;
    }
    return;
}

Token Scanner::StateMachine() {
    Token newToken;
    currentstate = init;
    while (currentstate != sFinal) {
        switch(currentstate) {
            case (init): // ----------------------------------------------- init CASE ---------------------------------------------------
                if(currentChar == EOF){
                    currentstate = sEOF;
                }
                /*
                else if (initial == 1) {
                    currentstate = sFinal;
                }
                */
                else if (currentChar == ','|| currentChar == '.'|| currentChar == '?'||
                    currentChar == '('|| currentChar == ')'|| currentChar == '*'||
                    currentChar == '+'|| currentChar == ':') {
                    currentstate = sChar; 
                }
                else if (IsWhiteSpace()) {
                    if (currentChar == '\n'|| currentChar == '\r') {
                        currentLine++;
                        currentstate = sWhiteSpace;
                    }
                    else if (currentChar == '\t') {
                        currentstate = sWhiteSpace;
                    }
                    currentstate = sWhiteSpace;
                } 
                else if (currentChar == '#') {
                    currentstate = sComment;
                }
                else if (currentChar == '\'') {
                    currentstate = sString;
                }
                else if (isalpha(currentChar)) {
                    currentstate = sSpecial;
                }
                else {
                    string mstr;
                    mstr += currentChar;
                    newToken.SetComplexValues("UNDEFINED", mstr, currentLine);
                    return newToken;
                }
                break;

            case (sChar): //----------------------------------------------- sChar CASE -----------------------------------------------------
            // ---------------------------------------- Identifies ":" ":-" "," "." "(" ")" "*" "+" ----------------------------------------
                if (currentChar == ':') {
                    nextChar = file.get();
                    if (nextChar == '-') {
                        newToken.SetValues(":-", currentLine);
                        return newToken;
                    }
                    else {
                        newToken.SetValues(":", currentLine);
                        nextCharVal = true;
                        return newToken;
                    }
                }
                else {
                    string mystring;
                    mystring += currentChar;
                    newToken.SetValues(mystring, currentLine);
                    return newToken;
                }
                break;

            case (sSpecial): // ----------------------------------------- sSpecial CASE ----------------------------------------------------
            // -----------------------------------------------I dentifies the "Facts", "Queries", "Rules", "Schemes" -----------------------
                facts = WordExtractor();
                if (currentChar == 'F') { // THIS IS TO IDENTIFY THE FACTS KEYWORD
                    if (facts == "Facts") {
                        newToken.SetValues(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = sID;
                    }
                }
                else if (currentChar == 'S') { // THIS IS TO IDENTIFY THE SCHEMES KEYWORD
                    if (facts == "Schemes") {
                        newToken.SetValues(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = sID;
                    }
                }
                else if (currentChar == 'Q') { // THIS IS TO IDENTIFY THE QUERIES KEYWORD
                    if (facts == "Queries") {
                        newToken.SetValues(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = sID;
                    }
                }
                else if (currentChar == 'R') { // THIS IS TO IDENTIFY THE RULES KEY WORD
                    if (facts == "Rules") {
                        newToken.SetValues(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = sID;
                    }
                }
                else {
                    currentstate = sID;
                }
                break;

            case (sComment)://---------------------------------------------------sComment-------------------------------------------------
            // not working for the special case that it reaches the end without getting the closing comment identifier
                nextChar = file.get();
                //block comment
                currentChar = nextChar;
                if (currentChar == '|') {
                    int otherlines = 0;
                    bool isEOF = false;
                    string bcom;
                    bcom = "#|";
                    currentChar = file.get();
                    nextChar = file.peek();
                    while (currentChar != EOF || nextChar != EOF) {
                        if (nextChar == '#' && currentChar == '|') {
                            bcom += "|#";
                            file.get();
                            newToken.SetComplexValues("COMMENT", bcom, currentLine);
                            currentLine =  currentLine + otherlines;
                            return newToken;
                        }
                        else if (nextChar == EOF) {
                            isEOF = true;
                        }

                        if (currentChar == '\r' || currentChar == '\n'){
                            otherlines = otherlines + 1;
                            bcom.append("\n");
                        }
                        else {
                            string cool;
                            cool += currentChar;
                            bcom.append(cool);
                        }
                        currentChar = file.get();
                        nextChar = file.peek();
                    }
                    if (isEOF) {
                        newToken.SetComplexValues("UNDEFINED", bcom, currentLine);
                        tokenList.push(newToken);//////////////////////////////////////////////////////////////////////////////////////////////
                        newToken.SetValues("EOF", currentLine + otherlines);/////////////////////////////////////////////////////////////////////////////////
                        currentChar = EOF;
                       return newToken;
                    }
                    else {
                        newToken.SetComplexValues("COMMENT", bcom, currentLine);
                        currentLine = currentLine + otherlines;
                        newToken.toString();
                        return newToken;
                    }
                    currentChar = file.get();
                }
                //line comment
                else {
                    string comment = "#";
                    comment = comment + currentChar;
                    nextChar = file.peek();
                    while (nextChar != '\n') {
                        currentChar = file.get();
                        comment = comment + currentChar;
                        nextChar = file.peek();
                        if (nextChar == '\r' || nextChar =='\n') {
                            break;
                        }
                    }
                    newToken.SetComplexValues("COMMENT", comment, currentLine);
                    return newToken;
                }
                
                
            break;
            case (sString)://-----------------------------------------------------sString CASE -------------------------------------
                currentChar = file.get();
                //general case: goes until reaches another '
                if (currentChar == '\'') {
                    string mstr = "\'";
                    int otherlines = 0;
                    while (currentChar != EOF) {
                        if (currentChar == '\r' || currentChar == '\n') {
                            otherlines++;
                        }
                        nextChar = file.peek();
                        if (currentChar == '\'' && nextChar == '\'') { // special case that back to back '' are found
                            currentChar = file.get();
                            nextChar = file.peek();
                            mstr = mstr + currentChar + "\'";

                        }
                        else if (currentChar == '\'' && nextChar != '\''){  // single ' is found
                            mstr = mstr + "\'";
                            newToken.SetComplexValues("STRING", mstr, currentLine);
                            currentLine = currentLine + otherlines;
                            return newToken;
                            break;
                        }
                        else if (nextChar == EOF) {
                            newToken.SetComplexValues("UNDEFINED", mstr, currentLine);
                            tokenList.push(newToken);/////////////////////////////////////////////////////////////////////
                            newToken.SetValues("EOF", currentLine + otherlines);////////////////////////////////////////////////////////
                            currentChar = EOF;
                            return newToken;
                            break;
                        }
                        else {
                            mstr = mstr + currentChar;
                        }
                        currentChar = file.get();
                    }
                }
                else if (currentChar == '\'') {
                    newToken.SetComplexValues("STRING", "\'\'", currentLine);
                    return newToken;
                }
                else {
                    string mstr = "\'";
                    int otherlines = 0;
                    while (currentChar != EOF) {
                        if (currentChar == '\r' || currentChar == '\n') {
                            otherlines++;
                        }
                        nextChar = file.peek();
                        if (currentChar == '\'' && nextChar == '\'') { // special case that back to back '' are found
                            currentChar = file.get();
                            nextChar = file.peek();
                            mstr = mstr + currentChar + "\'";

                        }
                        else if (currentChar == '\'' && nextChar != '\''){  // single ' is found
                            mstr = mstr + "\'";
                            newToken.SetComplexValues("STRING", mstr, currentLine);
                            currentLine = currentLine + otherlines;
                            return newToken;
                            break;
                        }
                        else if (nextChar == EOF) {
                            mstr += currentChar;
                            newToken.SetComplexValues("UNDEFINED", mstr, currentLine);
                            tokenList.push(newToken);/////////////////////////////////////////////////////////////////////
                            newToken.SetValues("EOF", currentLine + otherlines);////////////////////////////////////////////////////////
                            currentChar = EOF;
                            return newToken;
                            break;
                        }
                        else {
                            mstr = mstr + currentChar;
                        }
                        currentChar = file.get();
                    }
                }
            break;
            case (sID): //---------------------------------------------------------- sID CASE ---------------------------------------
                newToken.SetComplexValues("ID", facts, currentLine);
                return newToken;
                break;
            case (sEOF): // -------------------------------------------------------- EOF CASE ---------------------------------------
                newToken.SetValues("EOF", currentLine);
                return newToken;
                break;
            case (sWhiteSpace): //-------------------------------------------------- WhiteSpace CASE --------------------------------
                currentstate = sFinal;
                break;
            case (sFinal): // ------------------------------------------------------ sFinal CASE ------------------------------------
                return newToken;
                break;
            default:
                newToken.SetComplexValues("UNDEFINED", "UNDEFINED", currentLine);
        }   
    }
    newToken.SetComplexValues("UNDEFINED", "UNDEFINED", currentLine);
    return newToken;
}

queue <Token> Scanner::GetList() {
    return tokenList;
}