//
// Created by summe on 4/28/2024.
//

#include "Parameter.h"

using namespace std;

Parameter::Parameter(string name, string type){
    this->name = name;
    this->type = type;
    resolved = false;
    data = "";
}

void Parameter::resolve(std::string value) {
    data = value;
    resolved = true;
}