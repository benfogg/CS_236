#include "relation.h"

void Relation::AddTuple(Tuple tuples) {
    DemTuples.insert(tuples);
}
void Relation::SetScheme(Scheme DemSchemes) {
    TheScheme = DemSchemes;
} 
void Relation::SetName(string DatName){
    name = DatName;
}

Relation Relation::Select(int index, string value) {
    Relation NewRelation, NewRelation1;
    //cout << "Select 1" << endl;
    NewRelation.SetName(name);
    NewRelation.SetScheme(TheScheme);
    NewRelation1.SetName(name);
    NewRelation1.SetScheme(TheScheme);
    //Test -----------------------------------
    NewRelation1.SetName(name);
    NewRelation1.SetScheme(TheScheme);
    for (auto i: DemTuples) {
        NewRelation1.AddTuple(i);
    }
    //cout << "Test___BEFORE___TYPE1_________________________" << endl;
    //NewRelation1.ToString();
    //Test -------------------------------------

    for (auto i: DemTuples) {
        if (i.at(index) == value) {
            NewRelation.AddTuple(i);
        }
    }
    //==
    //cout << "Test___AFTER___TYPE1_________________________" << endl;
    //NewRelation.ToString();
    //==
    return NewRelation;
}
//Maybe needs work? #we will see ?????
Relation Relation::Select(int indexOne, int indexTwo){
    Relation NewRelation, NewRelation1;
    //cout << "Select 2" << endl;
    NewRelation.SetName(name);
    NewRelation.SetScheme(TheScheme);
//========================================================
    NewRelation1.SetName(name);
    NewRelation1.SetScheme(TheScheme);
    for (auto i: DemTuples) {
        NewRelation1.AddTuple(i);
    }
    //cout << "Test___BEFORE___TYPE2______________________" << endl;
    //NewRelation1.ToString();
//====================================================

    for (auto i: DemTuples) {
        if (i.at(indexOne) == i.at(indexTwo)) {
            NewRelation.AddTuple(i);
        }
    }
    //===
    //cout << "Test___AFTER___TYPE2_________________________" << endl;
   // NewRelation.ToString();
    //===
    return NewRelation;
}

Relation Relation::Project(vector<int> indicies){
    Relation NewRelation; // not pass in something??
    NewRelation.SetName(name);
    for (auto i: DemTuples){
        Tuple tempTuple;
        for(unsigned j = 0; j < indicies.size(); j++) {
            tempTuple.push_back(i.at(indicies.at(j)));
        }
        NewRelation.AddTuple(tempTuple);
    }
    Scheme TempScheme;
    for (unsigned int i = 0; i < indicies.size(); i++ ){
        TempScheme.Push_back(TheScheme.At(indicies.at(i)));
    }
    NewRelation.SetScheme(TempScheme);
    return NewRelation;
}

Relation Relation::Rename(vector<string> names){
    Scheme John;
    John.GetScheme(names);
    Relation NewRelation;
    NewRelation.SetName(name);
    NewRelation.SetScheme(John);
    for (auto i : DemTuples) {
        NewRelation.AddTuple(i);
    }
    return NewRelation;
}

string Relation::ToString() { // probably needs work
    string rString;
    
        for (auto i : DemTuples) {
            if (TheScheme.Size() != 0) {
                cout << "  ";
            }
            for (unsigned int j = 0; j < TheScheme.Size(); j++) {
                cout << TheScheme.At(j) + "=" + i.at(j);
                if (j < TheScheme.Size()-1) {
                    cout << ", ";
                }
            }
            if (TheScheme.Size() != 0) {
                cout << "\n";
            }
        }
        return rString;
}
