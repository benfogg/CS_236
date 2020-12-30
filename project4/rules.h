#pragma once
#include "predicate.h"

class Rule {
    public:
        void SetHeadPredicate(Predicate head);
        void SetRule(vector<Predicate> Toke);
        string ToString();
        Predicate Head;
        vector<Predicate> RuleList;
};
