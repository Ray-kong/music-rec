#include <iostream>
#include "lib/include/ApplicationController.h"

//#include "Gist.h"
//#include "AudioFile.h"
//#include "fileref.h"
#include "lib/include/SpotifyClient.h"

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

    // Demo call to spotify getRecommendations
//    if (argc < 2) {
//        return 1;
//    }
//    std::ifstream secretsFile{argv[1]};
//    std::string clientID, clientSecret;
//    secretsFile >> clientID >> clientSecret;
//    SpotifyClient thing{clientID, clientSecret};
//    auto res = thing.getRecommendations({"taylor swift"}, {"bad blood"});
//    for (const auto& part : res) {
//        std::cout << part->GetName() << std::endl;
//    }
}
