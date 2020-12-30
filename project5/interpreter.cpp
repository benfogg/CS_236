
#include "interpreter.h"

void Interpreter::SetDatalog(Datalog thisDatalog){
    theDatalog = thisDatalog;
    SchemesToDatabase(theDatalog.GetSchemes());
    FactsToDatabase(theDatalog.GetFacts());
    RuleOptimization(theDatalog.GetRules());
    //RelationRules(theDatalog.GetRules());
    cout << endl << "Query Evaluation" << endl;
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


void Interpreter::RelationRules(vector<Rule> Rules, bool trivial){
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
        }/*
        if (moreTuples) {
            cout << "should have more tuples" << endl;
        }
        else {
            cout << "no more tuples" <<  endl;
        }*/
        if (!trivial) {
            moreTuples = false;
            //cout << "IN EVALUATOR SAYS TRIVIAL !!!!!" <<endl;
        }
    }
    cout << rulesPass << " passes: ";
    return;
}

//==================================================================================================================
//================================Lab=5=Additions=============================================//
void Interpreter::RuleOptimization(vector<Rule>Rules) {
    //Title: Forward and Reverse Graphs
    Graph Forward, Backwards;
    vector<string> test;
    int open = (int) Rules.size();
    for (int i = 0; i < open; i ++) {
        Node newNode;
        newNode.id = i;
        newNode.isSelfDependent = false;
        Forward.nodeList.insert({i, newNode});
        Backwards.nodeList.insert({i, newNode});
    }
    for ( int i = 0; i < open; i++) {
        bool nodeAdded = false;
        //bool nodeAddedBackwards = false;
        int open1 = (int) Rules.at(i).RuleList.size();
        for (int j = 0; j < open1; j++) {
            for (int k = 0; k < open; k++) {
                if (Rules.at(i).RuleList.at(j).Name == Rules.at(k).Head.Name) {
                    bool dependent = false;
                    //cout << i<< ":";
                    if (i==k){
                        dependent = true;
                        //cout << "Dependent ++++++++++++++++++++++++++++++++++++++" << endl;
                    }/*
                    else {
                        cout << " NOT Dependent===================================" << endl;
                    }*/
                    //cout <<"forward from: " << i << " to: " << k << endl;
                    if(Forward.nodeList[i].isSelfDependent) {
                        dependent = true;
                        //cout << i << " is still true anyways" << endl;
                    }
                    Forward.addEdge(i,k, dependent);
                    //cout <<"backward from: " << k << " to: " << i << endl;
                    Backwards.addEdge(k,i, dependent);
                    nodeAdded = true;
                }
            }
            /*
            for (unsigned int d = 0; d < intslka.size(); d++) {
                cout << intslka.at(d);
            }
            */
        }
        if (!nodeAdded){ // if it is not dependent on anything......
            /*
            Node newNode;
            newNode.id = i;
            newNode.isSelfDependent = false;
            //cout << "here 1" << endl;
            Forward.nodeList.insert({i,newNode});
            //cout << "here 2" << endl;
            Backwards.nodeList.insert({i,newNode});
            */
        }
    }
    /*
    cout << "forward" << endl;
    for (auto i: Forward.nodeList) {
        cout << "key"<<i.first << "|" << "id:"<<i.second.id << "is dependent on: ";
        for(auto j: i.second.adjacencies) {
            cout << j;
        }
        cout <<  endl;
    }
    cout << "backwards" << endl;
    for (auto i: Backwards.nodeList) {
        cout << "key"<<i.first << "|" << "id:"<<i.second.id << "is dependent on: ";
        for(auto j: i.second.adjacencies) {
            cout << j;
        }
        cout <<  endl;
    }

    cout << "forwards" << endl;*/
    Forward.ToString();
    /*
    cout << "backwards" << endl;
    Backwards.ToString();*/
    //Run DFSforest on reserse graph creating a topological stack
    Backwards.dfsForest();
    Forward.topologicalSearch = Backwards.topologicalSearch;
    /*
    cout << "Topological search order: " << endl;
    while (Backwards.topologicalSearch.size() != 0) {
        cout << Backwards.topologicalSearch.top() << endl;;
        Backwards.topologicalSearch.pop();
    }
    */
    //Run DFS in topological order on forward graph
    Forward.dfsForestForward();
    /*
    cout << "Number of SCCs: " << Forward.scc.size() << endl;
    for (unsigned int i = 0; i < Forward.scc.size(); i++) {
        cout << "SCC " << i << " size: " << Forward.scc.at(i).size() << endl;;
    }
    */
    //Evaluate SCC trees 
    cout <<endl<< "Rule Evaluation" << endl;
    for(unsigned int i = 0; i < Forward.scc.size(); i ++) {
        vector<Rule> SpecificRules;
        string aunyong;
        unsigned int k = 0;
        bool trivial;
        //cout << "SCC SIZE: " << Forward.scc.size() <<  "++++++++++"<< endl;
        for(auto j: Forward.scc.at(i)) {
            //cout << "SCC SIZE: " << Forward.scc.at(i).size() <<  "++++++++++"<< endl;
            SpecificRules.push_back(Rules.at(j));
            string x = to_string(j);
    
            aunyong = aunyong + "R" + x;
            //cout << "thing: "<< j << endl;
            if (k != Forward.scc.at(i).size() - 1) {
                aunyong = aunyong + ",";
            }
            k++;
            /*
            cout << "SCC could be: " << endl;
            cout << "This is j:" << j<< endl;
            */
            trivial = Forward.nodeList[j].isSelfDependent;
/*
            if (Forward.nodeList[j].isSelfDependent) {
                cout << "IS NOT TRIVIAL\\\\\\\\\\\\" << endl;
            }
            else {
                cout << "Trivial////////" << endl;
            }*/
        }
        
        if (Forward.scc.at(i).size() != 1) {
            trivial = true;
        }

        cout << "SCC: " << aunyong << endl; 
        RelationRules(SpecificRules, trivial);
        cout << aunyong << endl;
    }

    return;
    
}
//================================Lab=5=Additions=============================================//


string Interpreter::ToString() {
    return theDatabase.ToStirng();
}
