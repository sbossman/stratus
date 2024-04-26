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

StratusFile::StratusFile(string file, string inputPath, string outputPath) {
    this->inputPath = inputPath;
    this->outputPath = outputPath;
    ifstream inputFile(inputPath + file);
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

    body = Body();
    body.readFromFile(inputFile, getImportedElements());

    cout << "Finished reading from file" << endl;



}


bool StratusFile::writeToFile(string file) {
    ofstream outFile(outputPath + file);
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

        string temp;
        bool flag = false;
        for(int i = 0; i < buffer.size(); i++){
            if(!isspace(buffer[i])) {
                temp += buffer[i];
                flag = true;
            }
            else if(flag){
                temp += buffer[i];
            }
        }
        buffer = temp;



        if(buffer.find(".css") != string::npos){
            ifstream importedFile(inputPath + buffer);
            if(!importedFile.is_open()){
                cerr << "File " << buffer << " does not exist!" << endl;
            }
            head.readInCSS(importedFile);
            importedFile.close();
        }
        else if(buffer.find(".str") != string::npos){
           string importFilename = "";
           int i = 0;
           while(!isspace(buffer[i])){
              importFilename += buffer[i];
              i++;
           }
           i++;
           cout << "Imported Stratus Filename: " << importFilename << endl;
           size_t findAs = buffer.find(" AS ");
           string useName;
           if(findAs != string::npos){
                for(int i = findAs + 4; i < buffer.size(); i++){
                    useName += buffer[i];
                }
           }
           else{
               for(int i = 0; i < buffer.size() - 4; i++){
                   useName += buffer[i];
               }
           }

           cout << "Using " << importFilename << " as " << useName << endl;

           StratusFile stratusFile = StratusFile(importFilename, inputPath, outputPath);
           head.addStyling(stratusFile.getHead().getStyling());
           importedSFs.emplace(useName,stratusFile);


        }
        else{
            cerr << "Unknown file type imported" << endl;
        }

    }
}

map<string, Body> StratusFile::getImportedElements() {
    map<string, Body> importedElems;
    for(auto elem : importedSFs){
       importedElems.emplace(elem.first, elem.second.getBody());
    }
    return importedElems;
}

map<string, Head> StratusFile::getImportedStyling(){
    map<string, Head> importedElems;
    for(auto elem : importedSFs){
        importedElems.emplace(elem.first, elem.second.getHead());
    }
    return importedElems;
}

Head StratusFile::getHead() {
    return head;
}

Body StratusFile::getBody(){
    return body;
}