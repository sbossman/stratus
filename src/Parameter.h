//
// Created by summe on 4/28/2024.
//
#pragma once
#include <iostream>

#ifndef STRATUS_PARAMETER_H
#define STRATUS_PARAMETER_H

using namespace std;

struct Parameter {
    string name;
    string type;
    string data;
    bool resolved;

    Parameter(string name, string type);
    void resolve(string value);
};


#endif //STRATUS_PARAMETER_H
