//
// Created by summe on 4/24/2024.
//
#include <vector>
#include <iostream>
#include <fstream>

#ifndef STRATUS_BODY_H
#define STRATUS_BODY_H

using namespace std;

struct Element{
    string tag;
    string details;
    string contents;
};

class Body {
    vector<string> TEMPLATE_BEGIN;
    vector<string> TEMPLATE_END;
    vector<string> temp;

    bool readElement(string buffer, ifstream file);

public:
    Body();

    bool readFromFile(ifstream& file);

    bool writeToFile(ofstream& file);

};


#endif //STRATUS_BODY_H
