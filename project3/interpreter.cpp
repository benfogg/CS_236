#include "interpreter.h"

void Interpreter::SetDatalog(Datalog thisDatalog){
    theDatalog = thisDatalog;
    SchemesToDatabase(theDatalog.GetSchemes());
    FactsToDatabase(theDatalog.GetFacts());
    RelationQueries(theDatalog.GetQueries());
}
void Interpreter::SchemesToDatabase(vector<Predicate> Predicates) {
    for(unsigned int i = 0; i < Predicates.size(); i++) {
        string theName = Predicates.at(i).GetName();
        Scheme theScheme;
        for (unsigned int j = 0; j < Predicates.at(i).ReturnVector().size(); j++) {
            theScheme.Push_back(Predicates.at(i).ReturnVector().at(j).ToString());
        }
        Relation newRelation;
        newRelation.SetName(theName);
        newRelation.SetScheme(theScheme);
        theDatabase.AddRelation(theName, newRelation);
    }
    
}
void Interpreter::FactsToDatabase(vector<Predicate> Facts) {
    for (unsigned int j = 0; j < Facts.size(); j++) {
        string theName;
        theName = Facts.at(j).GetName();
        Tuple theTuple;
        for(unsigned int i = 0; i < Facts.at(j).ReturnVector().size(); i++) {
            theTuple.push_back(Facts.at(j).ReturnVector().at(i).ToString());
        }
        /*
        cout << "Test for " << j  <<": " << endl;
        for (int i = 0; i < theTuple.size(); i ++) {
            cout << theTuple.at(i);
        }
        */
        theDatabase.AddTuplesToRelation(theName, theTuple);
    }
}
void Interpreter::RelationQueries(vector<Predicate> Queries){

    for (unsigned int i = 0; i < Queries.size(); i++) { // Individual queries
        
        string theName = Queries.at(i).GetName();
        vector<int> theInts;
        vector<string> theStrings;
        Relation thisRelation = theDatabase.databaseseses.at(theName);

        for (unsigned int j = 0; j < Queries.at(i).ReturnVector().size(); j++) { // individual Parameters
            Parameter currentParameter = Queries.at(i).ReturnVector().at(j);
            //cout << "currentParam: " << currentParameter.theParameter << endl;;
            if (currentParameter.IsString() == true) { // Seeing if the parameter is a constant
                //cout << "CONSTANT" << endl;
                string yes = currentParameter.theParameter;
                thisRelation = thisRelation.Select(j,yes);//Select One for Strings that are constants
            }
            else { //For variable parameters
                //cout << "NOT CONSTANT" << endl;
                bool duplicate = false;//=======
                for (unsigned int k = 0; k < theStrings.size(); k++) { //PROBLEM     
                    //cout << theStrings.at(k);//=======
                    if (theStrings.at(k) == currentParameter.theParameter) { // PROBLEM
                        //cout << "Duplicate" << endl;
                        duplicate = true;
                        thisRelation = thisRelation.Select(j,k);
                    }
                }
                if(duplicate == false) {
                    theStrings.push_back(currentParameter.theParameter);
                    theInts.push_back(j);
                }
                //cout << endl;//========
            }
        }
        Relation newRelation;
       
        newRelation = thisRelation.Project(theInts);
       
        thisRelation = newRelation.Rename(theStrings);
       

        cout << Queries.at(i).ToString() << "? ";
        if (thisRelation.DemTuples.size() == 0) {
            cout << "No\n";  
        }
        else {
            cout << "Yes(" << thisRelation.DemTuples.size() <<")\n";
            thisRelation.ToString();
        }
    }
}

//void Interpreter::RelationRules(vector<Rule> Rules){} // not in use during this lab

string Interpreter::ToString() {
    return theDatabase.ToStirng();
}