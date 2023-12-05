#include <iostream>
#include "lib/include/ApplicationController.h"

//#include "Gist.h"
//#include "AudioFile.h"
//#include "fileref.h"

int main(int argc, char* argv[]) {
    std::string inputDirectoryPath;

    if(argc == 2) {
        inputDirectoryPath = argv[1];
    } else {
        std::cout << "Please enter the path to the directory containing the input files: ";
        std::cin >> inputDirectoryPath;
    }

    ApplicationController controller;
    if(controller.setUp(inputDirectoryPath)) {
        controller.run();
    }

}
