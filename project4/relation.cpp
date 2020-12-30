
#include "relation.h"
//==================================================ADDED LAB 4====================================================//
Relation Relation::Join(Relation relationToJoin) {
    Relation NewRelation;
    vector <int> relationInts, toAddInts;
    NewRelation.TheScheme=TheScheme;
   
    for (unsigned int i = 0; i < relationToJoin.TheScheme.Size(); i++) {
        bool isACopy = false;
        //cout << "new==============================" << endl; 
        for (unsigned int j = 0; j < TheScheme.Size(); j++) {
            if (!isACopy) {
                //cout << TheScheme.At(j) << "|" << relationToJoin.TheScheme.At(i) << endl; 
                if (TheScheme.At(j) != relationToJoin.TheScheme.At(i)) {
                    isACopy = false;
                }
                else {
                    isACopy = true;
                }
            }

        }
        if (!isACopy) {
            NewRelation.TheScheme.Push_back(relationToJoin.TheScheme.At(i));
            toAddInts.push_back(i);
            //cout << "added:" << relationToJoin.TheScheme.At(i) << endl; 
        }
    }
   // cout << "scheme: " <<NewRelation.TheScheme.Fake() << endl;
    for (auto i: DemTuples) {
        for (auto j: relationToJoin.DemTuples) {
            if (isJoinable(i, j, TheScheme, relationToJoin.TheScheme)) {
                Tuple newTuple = i;
                for(unsigned int k = 0; k < toAddInts.size(); k++) {
                    newTuple.push_back(j.at(toAddInts.at(k)));
                }
                NewRelation.AddTuple(newTuple);
            }
        }
    }

    return NewRelation;
} 

bool Relation::isJoinable(Tuple Tuple1, Tuple Tuple2Add, Scheme Scheme1, Scheme Scheme2Add) {
    for (unsigned int i = 0; i < Scheme1.Size(); i++) {
        for (unsigned int j = 0; j < Scheme2Add.Size(); j++) {
            if (Scheme1.At(i) == Scheme2Add.At(j)) {
                if (Tuple1.at(i)!= Tuple2Add.at(j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Relation::Unite(Relation toUnite){
    bool returnval = false;
    for (auto i: toUnite.DemTuples) {
        if(DemTuples.insert(i).second) {
            returnval = true;
            //ToString();
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
    }
    return returnval;
}
//===================================================ADDED LAB 4==================================================//
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
    Relation NewRelation;
    NewRelation.SetName(name);
    NewRelation.SetScheme(TheScheme);
    
    for (auto i: DemTuples) {
        if (i.at(index) == value) {
            NewRelation.AddTuple(i);
        }
    }
    
    return NewRelation;
}


Relation Relation::Select(int indexOne, int indexTwo){
    Relation NewRelation, NewRelation1;
    NewRelation.SetName(name);
    NewRelation.SetScheme(TheScheme);

    for (auto i: DemTuples) {
        if (i.at(indexOne) == i.at(indexTwo)) {
            NewRelation.AddTuple(i);
        }
    }
    return NewRelation;
}

Relation Relation::Project(vector<int> indicies){
    //============================================//
    /*
        needs to be be altered for lab 4
    */
    //============================================//
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

void Relation::ToString() { 
    
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
        return;
}
