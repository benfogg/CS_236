
#include "interpreter.h"

void Interpreter::SetDatalog(Datalog thisDatalog){
    theDatalog = thisDatalog;
    SchemesToDatabase(theDatalog.GetSchemes());
    FactsToDatabase(theDatalog.GetFacts());
    RelationRules(theDatalog.GetRules());
    cout << "Query Evaluation" << endl;
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
    return;
}

void Interpreter::FactsToDatabase(vector<Predicate> Facts) {
    for (unsigned int j = 0; j < Facts.size(); j++) {
        string theName;
        theName = Facts.at(j).GetName();
        Tuple theTuple;
        for(unsigned int i = 0; i < Facts.at(j).ReturnVector().size(); i++) {
            theTuple.push_back(Facts.at(j).ReturnVector().at(i).ToString());
        }
        theDatabase.AddTuplesToRelation(theName, theTuple);
    }
    return;
}
void Interpreter::RelationQueries(vector<Predicate> Queries){

    for (unsigned int i = 0; i < Queries.size(); i++) {
        //=====
        //cout << "try new=====================================" << endl;
        Relation aRelation = EvalutatePredicate(Queries.at(i));
        cout << Queries.at(i).ToString() << "? ";
        if (aRelation.DemTuples.size() == 0) {
            cout << "No\n";  
        }
        else {
            cout << "Yes(" << aRelation.DemTuples.size() <<")\n";
            aRelation.ToString();
        }
    }
    return;
}
//===================================================================================================NEW PROJECT 4 =====================================================
Relation Interpreter::EvalutatePredicate(Predicate Queries) {
        string theName = Queries.GetName();
        vector<int> theInts;
        vector<string> theStrings;
        Relation thisRelation = theDatabase.databaseseses.at(theName);
        for (unsigned int j = 0; j < Queries.ReturnVector().size(); j++) { 
            Parameter currentParameter = Queries.ReturnVector().at(j);
            if (currentParameter.IsString() == true) {
                string yes = currentParameter.theParameter;
                thisRelation = thisRelation.Select(j,yes);
            }
            else { 
                bool duplicate = false;
                for (unsigned int k = 0; k < theStrings.size(); k++) {    
                    if (theStrings.at(k) == currentParameter.theParameter) { 
                        duplicate = true;
                        thisRelation = thisRelation.Select(j,k);
                    }
                }
                if(duplicate == false) {
                    theStrings.push_back(currentParameter.theParameter);
                    theInts.push_back(j);
                }
            }
        }
        thisRelation = thisRelation.Project(theInts);
        thisRelation = thisRelation.Rename(theStrings);
        return thisRelation;
}


void Interpreter::RelationRules(vector<Rule> Rules){
    cout << "Rule Evaluation" << endl;
    bool moreTuples = true;
    int rulesPass =0;
    while (moreTuples) {
        moreTuples = false;
        vector <bool> shouldGoOn;
        rulesPass++;
        for (unsigned int i = 0; i < Rules.size(); i ++) {
            cout << Rules.at(i).ToString()<< endl;
            vector <Relation> theRelations; 
            for (unsigned int j = 0; j < Rules.at(i).RuleList.size(); j ++ ) {
                Relation thisRelation = EvalutatePredicate(Rules.at(i).RuleList.at(j));
                theRelations.push_back(thisRelation);
            }
            
            // Join
            Relation thisRelation;
            if (theRelations.size() > 1) {
                thisRelation = theRelations.at(0);
                for (unsigned int j = 0; j < theRelations.size()-1; j++ ) {
                    thisRelation = thisRelation.Join(theRelations.at(j+1));
                }
            }
            else {
                thisRelation = theRelations.at(0);
            }
            //Project
            //What the heck is going on???
            vector <int> Indicies;
            for (unsigned int j = 0; j < Rules.at(i).Head.parameterList.size(); j++) {
                //cout << Rules.at(i).Head.parameterList.at(j).ToString() << " | " << thisRelation.TheScheme.Fake();
                for (unsigned int k = 0; k < thisRelation.TheScheme.Size(); k++) {
                    //cout << Rules.at(i).Head.parameterList.at(j).theParameter << "|" << thisRelation.TheScheme.At(k) << endl;
                    if (Rules.at(i).Head.parameterList.at(j).theParameter == thisRelation.TheScheme.At(k)) {
                        Indicies.push_back(k);
                        //cout << "got pushed back" << endl;
                    }
                }
            }
            //cout << "indicies: " <<Indicies.size() << endl;
            thisRelation = thisRelation.Project(Indicies);
            //Rename
            thisRelation.name = Rules.at(i).Head.Name;
            if (theDatabase.databaseseses.at(thisRelation.name).TheScheme.values.size() == thisRelation.TheScheme.values.size()) {
                thisRelation.TheScheme = theDatabase.databaseseses.at(thisRelation.name).TheScheme;
            }
            else {
                //cout << "abort" << endl;
            }
            /*
            cout << "Scheme end:" ;
            for (unsigned int i = 0; i < theDatabase.databaseseses.at(thisRelation.name).TheScheme.values.size(); i++) {
                cout << theDatabase.databaseseses.at(thisRelation.name).TheScheme.values.at(i);
            }
            cout << endl;
            thisRelation.Rename(theDatabase.databaseseses.at(thisRelation.name).TheScheme.values);
            cout << "Scheme end:" ;
            for (unsigned int i = 0; i < thisRelation.TheScheme.values.size(); i++) {
                cout << thisRelation.TheScheme.values.at(i);
            }
            */
            //Union
            shouldGoOn.push_back(theDatabase.databaseseses.at(thisRelation.name).Unite(thisRelation));
        
            //output
            /*
            if (theDatabase.databaseseses.at(thisRelation.name).DemTuples.size() == 0) {}
            else {
                if (theDatabase.databaseseses.at(thisRelation.name).BeenOutPutted == false) {
                    thisRelation.ToString();
                }
            }  
            */
        }
        for (unsigned int a = 0; a <shouldGoOn.size(); a++) {
            if (shouldGoOn.at(a)) {
                moreTuples = true;
            } 
        }
    }
    cout << endl << "Schemes populated after " << rulesPass << " passes through the Rules." << endl << endl;;
    return;
}

//==================================================================================================================
string Interpreter::ToString() {
    return theDatabase.ToStirng();
}
