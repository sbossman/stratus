//
// Created by summe on 4/24/2024.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

#include "StratusFile.h"

using namespace std;

StratusFile::StratusFile(string file, string inputPath, string outputPath) {
    BEGIN_BODY.push_back("<body>");

    END_BODY.push_back("</body>");
    END_BODY.push_back("</html>");

    this->inputPath = inputPath;
    this->outputPath = outputPath;
    ifstream inputFile(inputPath + file);
    if(!inputFile.is_open()){
        cerr << "File " << inputPath + file << " not found" << endl;
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
        else if(buffer.size() > 10 && buffer.substr(0, 10) == "PARAMETERS"){
            readParameters(inputFile, buffer);
        }

    }

    readBody(inputFile);



}


bool StratusFile::writeToFile(string file) {
    ofstream outFile(outputPath + file);
    head.writeToFile(outFile);
    for(int i = 0; i < BEGIN_BODY.size(); i++){
        outFile << BEGIN_BODY[i] << endl;
    }
    for(int i = 0; i < temp.size(); i++){
        outFile << temp[i] << endl;
    }
    for(int i = 0; i < END_BODY.size(); i++){
        outFile << END_BODY[i] << endl;
    }
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
           while(!isspace(buffer[i]) && i < buffer.size()){
              importFilename += buffer[i];
              i++;
           }
           i++;
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


           StratusFile stratusFile = StratusFile(importFilename, inputPath, outputPath);
           head.addStyling(stratusFile.getHead().getStyling());
           importedSFs.emplace(useName,stratusFile);


        }
        else{
            cerr << "Unknown file type imported" << endl;
        }

    }
    cerr << "IMPORT statement must end with '}' on a newline" << endl;
}

bool StratusFile::readParameters(std::ifstream &file, string currLine) {
    string buffer;
    while(getline(file, buffer)){
        if(buffer == "}"){
            return true;
        }
        istringstream line(buffer);
        string type;

        while(type == "")
            getline(line, type, ' ');


        if(type != "STRING" && type != "FILE"){
            cout << "Incorrect parameter type " << type << "." << endl;
            return false;
        }

        string varName;
        getline(line, varName);
        if(varName[varName.size()-1] == ','){
            varName = varName.substr(0, varName.size()-1);
        }
        Parameter p = Parameter(varName, type);
        parameters.emplace(varName, p);

    }
}

bool StratusFile::readBody(std::ifstream &file) {
    string buffer;
    stack<string> tag_stack;

    while(getline(file, buffer)){
        int i = 0;
        while(isspace(buffer[i])){
            i++;
        }
        if(buffer[i] == '_'){
            i++;
            bool importedElem = false;
            // It's an imported element
            if(buffer[i] == '_'){
                importedElem = true;
                i++;
            }
            // It's a normal HTML element
            string tag = "";
            while(buffer[i] != '('){
                tag += buffer[i];
                i++;
            }
            if(!importedElem)
                tag_stack.push(tag);

            i++;
            string details;
            while(buffer[i] != ')'){
                details += buffer[i];
                i++;
            }
            i++;
            if(importedElem){
                map<string, string> params;
                string currName;
                string currVal;
                bool onVal = false;
                for(int i = 0; i < details.size(); i++){
                    if(details[i] == ','){
                        onVal = false;
                        params.emplace(currName, currVal);
                        currName = "";
                        currVal = "";
                    }
                    else if(details[i] == '='){
                        onVal=true;
                    }
                    else{
                        if(onVal){
                            currVal += details[i];
                        }
                        else{
                            currName += details[i];
                        }
                    }
                }
                if(details.size() > 3){
                    params.emplace(currName, currVal);
                }
                importedSFs.at(tag).resolveParameters(params);

                // Parameters now resolved and contained in parameters map
                for(auto iter = parameters.begin(); iter != parameters.end(); iter++){
                    cout << iter->first << ": " << iter->second.data << endl;
                }

                // Goes into SF file and pushes back the element import stuff
                // (ie gets the element vector and adds it to the print out list)
                vector<string> elemImport = importedSFs.at(tag).getElemVect();
                for(int j = 0; j < elemImport.size(); j++){
                    temp.push_back(elemImport[j]);
                }
            }
            else{
                while(buffer[i] != '{'){
                    i++;
                }
                i++;
                temp.push_back("<" + tag + " " + details + ">");

                // Reading rest of line
                string restOfLine;
                bool flag = true;
                while(i < buffer.size()){
                    if(buffer[i] == '}'){
                        temp.push_back(restOfLine);
                        flag = false;
                        string tag = tag_stack.top();
                        tag_stack.pop();
                        temp.push_back("</" + tag + ">");
                    }
                    restOfLine += buffer[i];
                    i++;
                }
                if(flag){
                    temp.push_back(restOfLine);
                }
            }

        }
        else if(buffer[i] == '}'){
            if(tag_stack.size() == 0){
                cerr << "Missing opening bracket somewhere" << endl;
            }
            string tag = tag_stack.top();
            tag_stack.pop();
            temp.push_back("</" + tag + ">");
        }
        else{
            temp.push_back(buffer);
        }

    }
    if(tag_stack.size() > 0){
        cerr <<  "Too many opening brackets! Missing closing bracket somewhere" << endl;
    }
    return true;
}

//map<string, Body> StratusFile::getImportedElements() {
//    map<string, Body> importedElems;
//    for(auto elem : importedSFs){
//       importedElems.emplace(elem.first, elem.second.getBody());
//    }
//    return importedElems;
//}

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


vector<string> StratusFile::getElemVect() {
    vector<string> elemVect;

    //TODO: Make this not so scuffed
    // (rn it is literally just looping through the element vector
    //   and resolving parameters)
    for(int l = 0; l < temp.size(); l++){
        string line;
        string p;
        bool onParam = false;
        for(int i = 0; i < temp[l].size(); i++){
            //TODO: add [[ and ]] handling
            if(temp[l][i] == '['){
                onParam = true;
            }
            else if(temp[l][i] == ']'){
                onParam = false;
                cout << "PARAMETER: " << p << endl;
                Parameter prm = parameters.at(p);
                if(prm.type == "STRING"){
                    line += prm.data;
                }
                else if(prm.type == "FILE"){
                    ifstream prmFile(inputPath + prm.data);
                    string readIn;
                    if(!prmFile.is_open()){
                        cerr << "FILE " << prm.data << " NOT OPEN" << endl;
                    }
                    while(getline(prmFile, readIn)){
                        line += readIn + "<br>";
                    }
                }
                else{
                    cerr << "UNKNOWN TYPE FOR " << prm.name << endl;
                }
                p = "";
            }
            else if(onParam){
                p += temp[l][i];
            }
            else{
                line += temp[l][i];
            }
        }
        elemVect.push_back(line);
    }
    return elemVect;
}

bool StratusFile::resolveParameters(map<std::string, std::string>& params) {
    for(auto iter = params.begin(); iter != params.end(); iter++){
         try{
            string name = iter->first;
            string value = iter->second;

            parameters.at(name).resolve(value);
         }
         catch(...){
            cerr << "Parameter " << iter->first << " not found" << endl;
         }
    }
    bool allResolved = true;
    for(auto iter = parameters.begin(); iter != parameters.end(); iter++){
        if(!iter->second.resolved){
            cout << "Not: " << iter->second.name << "." << endl;
            allResolved = false;
        }
        else{
            cout << "Resolved: " << iter->second.name << endl;
            cout << "\t " << iter->second.data << endl;
        }
    }
    if(!allResolved && parameters.begin() != parameters.end()){
        cout << "NOT ALL RESOLVED" << endl;
    }
    return allResolved;
}


