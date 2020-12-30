#pragma once
using namespace std;
#include <string>
#include <vector>
#include <iostream>

class Scheme{
    vector <string> values;
    public:
    unsigned int Size() {
        return values.size();
    }
    void Push_back(string addstring) {
        values.push_back(addstring);
        return;
    }
    void GetScheme(vector<string> john) {
        values = john;

    }
    string At(int i) {
        return values.at(i);
    }
};
