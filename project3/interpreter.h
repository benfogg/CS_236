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
        //void RelationRules(vector<Rule> Rules);
        
        string ToString();
    /*
        for each scheme `s'
            create a relation using name and scheme from `s'
        
        for each fact `f'
            make a tuple `t' using the values from `f'
            add `t' to relation `r' with the same name as `f'
        
        for each query `q'
            get the relation `r' with the same name as the query `q'
            select the tuples that match the query `q'
            (run a select for each parameter in the query)
            project using the positions of the variables in `q'
            rename to match the names of variables in `q'
            print the resulting relation
    */
};