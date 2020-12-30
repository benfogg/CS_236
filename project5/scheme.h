#pragma once
using namespace std;
#include <string>
#include <vector>
#include <iostream>

class Scheme{
    public:
    vector <string> values;
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

    string Fake() {
        string stringy;
        for (unsigned int i = 0; i < values.size(); i ++) {
            stringy += values.at(i);
        }
        return stringy;
    }
};
