#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    ifstream file("../input/index.str");
    string buffer;
    vector<string> body;
    vector<string> header;


    while(getline(file, buffer)){
        cout << buffer << endl;
    }

    return 0;
}
