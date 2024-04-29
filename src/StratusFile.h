//
// Created by summe on 4/24/2024.
//
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "Body.h"
#include "Head.h"
#include "Parameter.h"

#ifndef STRATUS_STRATUSFILE_H
#define STRATUS_STRATUSFILE_H

using namespace std;

class StratusFile {
    Head head;
    string inputPath;
    string outputPath;
    // Imported Stratus Files, strings are their names
    map<string, StratusFile> importedSFs;
    // Key is parameter name, value is type (STRING or FILE)
    map<string, Parameter> parameters;

    vector<string> BEGIN_BODY;
    vector<string> END_BODY;
    vector<string> temp;



    bool readImports(ifstream& file);
    bool readParameters(ifstream &file, string currLine);
    bool readBody(ifstream& file);

public:
    StratusFile(string file, string inputPath, string outputPath);

    bool resolveParameters(map<string, string> params);

    bool writeToFile(string file);

//    map<string, Body> getImportedElements();
    map<string, Head> getImportedStyling();

//    Body getBody(); //TODO: replace with getElemVect
    vector<string> getElemVect();
    Head getHead();


};


#endif //STRATUS_STRATUSFILE_H
