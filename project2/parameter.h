#pragma once
#include "string"
using namespace std;

class Parameter {
    public:
        void SetParam(string param);
        string ToString();
    private:
        string theParameter; // Needs to be changed to string
};