//
// Created by summe on 4/24/2024.
//

#include "Body.h"

using namespace std;

Body::Body(){
   TEMPLATE_BEGIN.push_back("<body>");

   TEMPLATE_END.push_back("</body>");
   TEMPLATE_END.push_back("</html>");
}

bool Body::readFromFile(std::ifstream &file) {
    return true;
}

bool Body::writeToFile(std::ofstream &file) {
    for(int i = 0; i < TEMPLATE_BEGIN.size(); i++){
        file << TEMPLATE_BEGIN[i] << endl;
    }
    for(int i = 0; i < TEMPLATE_END.size(); i++){
        file << TEMPLATE_END[i] << endl;
    }
    return true;
}