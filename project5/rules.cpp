#include "rules.h"


void Rule::SetHeadPredicate(Predicate head) {
    Head = head;
}

void Rule::SetRule(vector<Predicate> Toke) {
    for (unsigned int i = 0; i < Toke.size(); i++) {
        RuleList.push_back(Toke.at(i));
    }
}

string Rule::ToString() {
    string theRule;
    theRule = Head.ToString() + " :- ";
    for (unsigned int i = 0; i < RuleList.size(); i++) {
        if ( i == 0) {
            theRule = theRule + RuleList.at(i).ToString();
        }
        else {
            theRule = theRule + "," + RuleList.at(i).ToString();
        }

    } 
    theRule += ".";
    return theRule;
}