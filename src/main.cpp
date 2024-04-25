#include <iostream>
#include <fstream>
#include <vector>

#include "./StratusFile.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    StratusFile file = StratusFile("../input/index.str");

    file.writeToFile("../output/index.html");

    return 0;
}
