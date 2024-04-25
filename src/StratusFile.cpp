//
// Created by summe on 4/24/2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "StratusFile.h"

using namespace std;

StratusFile::StratusFile(string file) {
    ifstream inputFile(file);
    if(!inputFile.is_open()){
        cout << "FILE NOT OPEN" << endl;
    }

    string buffer;
    head = Head();

    while(getline(inputFile, buffer)){
        if(buffer == "BODY"){
            break;
        }
        else if(buffer.find("IMPORT") != string::npos){
            readImports(inputFile);
        }
        else if(buffer.substr(0, 5) == "TITLE"){
            int first_char = 5;
            while(buffer[first_char] != '='){
                first_char++;
            }
            first_char++;
            string title = "";
            for(int i = first_char; i < buffer.size(); i++){
                title += buffer[i];
            }
            head.setTitle(title);
        }

    }

    while(getline(inputFile, buffer)){
        cout << buffer << endl;
    }


}


bool StratusFile::writeToFile(string file) {
    ofstream outFile(file);
    head.writeToFile(outFile);
    body.writeToFile(outFile);
    return true;
}

bool StratusFile::readImports(ifstream& file){
    string buffer;
    while(getline(file, buffer)){
        if(buffer == "}"){
            return true;
        }

        //TODO: Remove spaces from buffer
        string temp;
        for(int i = 0; i < buffer.size(); i++){
            if(!isspace(buffer[i])){
                temp += buffer[i];
            }
        }
        buffer = temp;
        cout << buffer << endl;

        ifstream cssFile(buffer);
        if(!cssFile.is_open()){
            cerr << "File " << buffer << " does not exist!" << endl;
        }
        head.readInCSS(cssFile);
        cssFile.close();
    }
}