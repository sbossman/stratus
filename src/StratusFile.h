//
// Created by summe on 4/24/2024.
//
#include "./Head.h"
#include "./Body.h"
#include <iostream>
#include <fstream>
#include <vector>

#ifndef STRATUS_STRATUSFILE_H
#define STRATUS_STRATUSFILE_H

using namespace std;

class StratusFile {
    Head head;
    Body body;

public:
    StratusFile(string file);

    bool writeToFile(string file);

};


#endif //STRATUS_STRATUSFILE_H
