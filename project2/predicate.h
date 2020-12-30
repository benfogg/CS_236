#pragma once
#include "parameter.h"
#include <vector>

class Predicate {
    public:
        void SetName(string theName);
        vector<Parameter> ReturnVector();
        void PushPredicate(Parameter theParameter);
        string ToString();
    private:
        vector<Parameter> parameterList;
        string Name;
};