#pragma once
#include "token.h"
#include "datalog.h"
#include "expression.h"
#include <queue>

class Parser {
    public:
        Parser();
        ~Parser();

        bool DatalogProgram(queue<Token> Tokens);
        string ToString();
//__________________________________PROJECT 3 ALLTERATIONS (below)____________________________________________________________________________________
        Datalog GetDatalog();
//__________________________________PREJECT 3 ALLTERATIONS (above)____________________________________________________________________________________
protected:
        void PrintFail(int i = 0);
        bool CheckNext(TokenType type);

        Datalog Parse(queue<Token> Tokens);
        bool ParseCheck(TokenType type);
        Predicate ParseScheme();
        vector<Predicate> ParseSchemeList(vector<Predicate> Schemes);
        void ParseIDList();
        vector<Predicate> ParseFactList(vector<Predicate> Facts);
        Predicate ParseFact();
        void ParseStringList();
        vector<Rule> ParseRuleList(vector<Rule> Rules);
        Rule ParseRules();
        Predicate ParseQuery();
        vector<Predicate> ParseQueryList(vector<Predicate> Queries);

        Predicate ParseHeadPredicate();
        Predicate ParsePredicate();
        vector<Predicate> ParsePredicateList(vector<Predicate>);

        Parameter ParseParameter();
        void ParseParameterList();
        string ParseExpression();
        Token ParseOperator();

        void PushOnList(string token, bool torf);
//VARIABLES
        vector<Parameter> paramList;
        queue<Token> TokenQueue;
        Token thisToken;
        Token nextToken;
        bool fail = false;
        Datalog Everything;
        set<string> Domain;
};