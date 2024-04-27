//
// Created by summe on 4/24/2024.
//

#include "Body.h"
#include <stack>

using namespace std;

Body::Body(){
   TEMPLATE_BEGIN.push_back("<body>");

   TEMPLATE_END.push_back("</body>");
   TEMPLATE_END.push_back("</html>");
}

bool Body::readFromFile(std::ifstream &file, map<string, Body> importedElements) {
    string buffer;
    stack<string> tag_stack;

    while(getline(file, buffer)){
        int i = 0;
        while(isspace(buffer[i])){
            i++;
        }
        if(buffer[i] == '_'){
            i++;
            string tag = "";
            while(buffer[i] != '('){
                tag += buffer[i];
                i++;
            }
            tag_stack.push(tag);

            i++;
            string details;
            while(buffer[i] != ')'){
                details += buffer[i];
                i++;
            }
            i++;
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
        else if(buffer[i] == '}'){
            string tag = tag_stack.top();
            tag_stack.pop();
            temp.push_back("</" + tag + ">");
        }
        else if(buffer[i] == '['){
            i++;
            string elemName;
            for(int j = i; j < buffer.size(); j++){
                if(!isspace(buffer[j]) && buffer[j] != ']'){
                    elemName += buffer[j];
                }
            }
            vector<string> elemImport = importedElements[elemName].getElemVect();
            for(int j = 0; j < elemImport.size(); j++){
                temp.push_back(elemImport[j]);
            }

        }
        else{
            temp.push_back(buffer);
        }

    }
    return true;
}

bool Body::writeToFile(std::ofstream &file) {
    for(int i = 0; i < TEMPLATE_BEGIN.size(); i++){
        file << TEMPLATE_BEGIN[i] << endl;
    }
    for(int i = 0; i < temp.size(); i++){
        file << temp[i] << endl;
    }
    for(int i = 0; i < TEMPLATE_END.size(); i++){
        file << TEMPLATE_END[i] << endl;
    }
    return true;
}

bool Body::readElement(std::string buffer, ifstream file) {
    return true;

}

vector<string> Body::getElemVect() {
    return temp;
}