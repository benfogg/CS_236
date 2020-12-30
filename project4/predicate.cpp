 #include "predicate.h"

void Predicate::SetName(string theName) {
    Name = theName;
}

void Predicate::PushPredicate(Parameter theParameter) {
    parameterList.push_back(theParameter);
    return;
}
string Predicate::ToString() {
    string Pstring = Name + "(";
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        
        if (i ==0 ){
            Pstring = Pstring + parameterList.at(i).ToString();
        }
        else {
            Pstring = Pstring + "," + parameterList.at(i).ToString();
        }
    }
    Pstring = Pstring + ")";
    return Pstring;
}

vector<Parameter> Predicate::ReturnVector() {
    return parameterList;
}