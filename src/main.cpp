#include <iostream>
#include <fstream>
#include <vector>

#include "./StratusFile.h"

using namespace std;

int main(int argc, char* argv[]) {

//    StratusFile file = StratusFile("../input/index.str");

//    file.writeToFile("../output/index.html");
    if(argc < 4 ){ //|| argc != 4 || argv[1] == "-help"){
        cout << "Arguments should be passed in with syntax:" << endl;
        cout << "\t [filelist].txt [input dir]/ [output dir]/" << endl;
        return 1;
    }

    string listFilename = argv[1];
    string inputDir = argv[2];
    string outputDir = argv[3];

    ifstream listFile(listFilename);
    vector<string> filesToRead;
    string temp;
    while(getline(listFile, temp)){
        ifstream test(inputDir + temp);
        if(!test.is_open()){
            cerr << "No such file as " << inputDir + temp << endl;
        }
        if(temp.size() < 5 || temp.find(".str") == string::npos){
            cerr << "Not of correct file type (must be a .str file)" << endl;
        }
        test.close();
        filesToRead.push_back(temp);
    }

    for(int i = 0; i < filesToRead.size(); i++){
        StratusFile file = StratusFile(filesToRead[i], inputDir, outputDir);

        string output = filesToRead[i].substr(0, filesToRead[i].size()-4) + ".html";
        cout << "ouput: " << output << endl;
        file.writeToFile(output);
    }


    return 0;
}
