#pragma once
#include "database.h"
#include "datalog.h"

class Interpreter {
    private:
        Database theDatabase;
        Datalog theDatalog;
    public:
        void SetDatalog(Datalog theInformation);

        void SchemesToDatabase(vector<Predicate> Schemes);
        void FactsToDatabase(vector<Predicate> Facts);
        void RelationQueries(vector<Predicate> Queries);
//======================================Added in Lab 4 =====================================================//
        void RelationRules(vector<Rule> Rules);
        Relation EvalutatePredicate(Predicate Predicates);
//======================================Added in Lab 4 =====================================================//
        string ToString();
};