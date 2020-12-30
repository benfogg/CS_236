#pragma once
#include "relation.h"
#include <map>

class Database {
    //map<string, Relation> databaseseses;

public:
    map<string, Relation> databaseseses;
    void AddRelation(string Name, Relation newRelation) { // how the hell am I supposed to know 
        databaseseses.insert({Name, newRelation});
        return;
    }
    void AddTuplesToRelation(string Name, Tuple theTuple) {
        databaseseses.at(Name).AddTuple(theTuple);
        return;
    }
    string ToStirng() {
        string stringy;
        map<string, Relation> ptr;
        for (auto i: databaseseses) {
            stringy  =  i.first + ": \n" + i.second.ToString();
        }
        return stringy;
    }
    Relation GetRelation(string Name) {
        return databaseseses.at(Name);
    }
};
