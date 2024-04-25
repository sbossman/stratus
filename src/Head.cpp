//
// Created by summe on 4/24/2024.
//

#include "Head.h"
using namespace std;

Head::Head(){

    TEMPLATE_BEGIN.push_back("<!DOCTYPE html>");
    TEMPLATE_BEGIN.push_back("<html lang=\"en\">");
    TEMPLATE_BEGIN.push_back("<head>");
    TEMPLATE_BEGIN.push_back("\t<meta charset=\"UTF-8\">");
    TEMPLATE_BEGIN.push_back("\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    TEMPLATE_BEGIN.push_back("\t<title>My Website</title>");
    TEMPLATE_BEGIN.push_back("\t<style>");

    TEMPLATE_END.push_back("\t</style>");
    TEMPLATE_END.push_back("</head>");

    title = "My Website";
}

Head::Head(string title) : Head(){

    TEMPLATE_BEGIN.push_back("<!DOCTYPE html>");
    TEMPLATE_BEGIN.push_back("<html lang=\"en\">");
    TEMPLATE_BEGIN.push_back("<head>");
    TEMPLATE_BEGIN.push_back("\t<meta charset=\"UTF-8\">");
    TEMPLATE_BEGIN.push_back("\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    TEMPLATE_BEGIN.push_back("\t<title>" + title + "</title>");
    TEMPLATE_BEGIN.push_back("\t<style>");

    TEMPLATE_END.push_back("\t</style>");
    TEMPLATE_END.push_back("</head>");

    this->title = title;
}

void Head::setTitle(std::string title) {
    TEMPLATE_BEGIN[5] = "\t<title>" + title + "</title>";
    this->title = title;
}

bool Head::readInCSS(std::ifstream &file) {
    string buffer;
    while(getline(file, buffer)){
        styling.push_back("\t\t" + buffer);
    }
    return true;
}

bool Head::writeToFile(std::ofstream &file) {
    for(int i = 0; i < TEMPLATE_BEGIN.size(); i++){
        file << TEMPLATE_BEGIN[i] << endl;
    }
    for(int i = 0; i < styling.size(); i++){
        file << styling[i] << endl;
    }
    for(int i = 0; i < TEMPLATE_END.size(); i++){
        file << TEMPLATE_END[i] << endl;
    }
    return true;
}
