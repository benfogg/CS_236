#pragma once
#include "string"
using namespace std;

class Parameter {
    public:
        void SetParam(string param);
        string ToString();
        void SetBool(bool trueOrFalse) {
            boolString = trueOrFalse;
        }
        bool IsString() {
            return boolString;
        }
        string theParameter; // Needs to be changed to string
        bool boolString;
};