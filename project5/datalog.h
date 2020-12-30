#pragma once
#include <set>
#include "rules.h"

enum PredicateType{Facts,Queries,Schemes};

class Datalog {
    public:
        void SetFacts(vector<Predicate> Fact);
        void SetQueries(vector<Predicate> Query);
        void SetSchemes(vector<Predicate> Scheme);
        void SetRules(vector<Rule> Rule);
        vector<Rule> GetRules();
        vector<Predicate> GetQueries();
        vector<Predicate> GetFacts();
        vector<Predicate> GetSchemes();
        void SetDomain(set<string> Set);
        string ToString();
    private:
        vector<Rule> Rules;
        vector<Predicate> Facts;
        vector<Predicate> Queries;
        vector<Predicate> Schemes;
        set<string> Domain;
};