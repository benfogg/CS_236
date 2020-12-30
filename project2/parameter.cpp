#include "parameter.h"

void Parameter::SetParam(string Toke){
    theParameter = Toke;
}

string Parameter::ToString(){
    return theParameter;
}