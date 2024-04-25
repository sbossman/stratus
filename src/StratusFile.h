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

#ifndef STRATUS_STRATUSFILE_H
#define STRATUS_STRATUSFILE_H

using namespace std;

class StratusFile {
    Head head;
    Body body;
    map<string, StratusFile> importedSFs;


    bool readImports(ifstream& file);

public:
    StratusFile(string file);

    bool writeToFile(string file);

    map<string, Body> getImportedElements();
    map<string, Head> getImportedStyling();

    Body getBody();
    Head getHead();


};


#endif //STRATUS_STRATUSFILE_H
