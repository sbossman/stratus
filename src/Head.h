//
// Created by summe on 4/24/2024.
//
#include <iostream>
#include <fstream>
#include <vector>

#ifndef STRATUS_HEAD_H
#define STRATUS_HEAD_H
using namespace std;

class Head {
    vector<string> TEMPLATE_BEGIN;
    vector<string> TEMPLATE_END;
    vector<string> styling;
    string title;

public:
    Head();
    Head(string title);

    bool readInCSS(ifstream& file);

    bool writeToFile(ofstream& file);

};


#endif //STRATUS_HEAD_H
