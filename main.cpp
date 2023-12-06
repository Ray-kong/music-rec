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
//    auto res = thing.getRecommendations({thing.getArtist("taylor swift").GetId()},
//                                        {thing.getTrack("bad blood", "taylor swift").GetId()});
//    for (const auto& part : res) {
//        std::cout << part->GetName() << std::endl;
//        std::cout << part->GetAlbum()->GetName() << std::endl;
//        std::cout << part->GetArtists()[0]->GetName() << std::endl;
//        std::cout << std::endl;
//    }
//
//    auto weaker = thing.getRecommendation(res);
//
//    std::cout << weaker.GetName() << std::endl;
//    std::cout << weaker.GetAlbum()->GetName() << std::endl;
//    std::cout << weaker.GetArtists()[0]->GetName() << std::endl;
}
