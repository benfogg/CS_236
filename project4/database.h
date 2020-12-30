#pragma once
#include "relation.h"
#include <map>
#include <sstream>

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
        stringstream stringy;
        map<string, Relation> ptr;
        for (auto i: databaseseses) { // Problems out putting look here and check with project 3
            cout  <<  i.first << ": \n";
            i.second.ToString();
        }
        return stringy.str();
    }
    
    Relation GetRelation(string Name) {
        return databaseseses.at(Name);
    }
    int TupleQuantity() {
        int size = 0;
        for (auto i: databaseseses) {
            cout << "This is the Size: ";
            size += i.second.GetTupleSize();
            cout << size << endl;
        }
        return size;
    }
};
