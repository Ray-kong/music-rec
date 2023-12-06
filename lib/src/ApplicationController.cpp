//
// Created by Ray Kong on 12/3/23.
//

#include "../include/ApplicationController.h"
#include "../include/MusicLibraryProcessor.h"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

bool ApplicationController::setUp(std::string inputDirectoryPath, std::string clientID, std::string clientSecret) {
    spotify.setAuthentication(clientID, clientSecret);

    std::cout << "checking if path is dir..." << std::endl;
    if (fs::exists(inputDirectoryPath) && fs::is_directory(inputDirectoryPath)) {
        std::cout << "path is dir" << std::endl;
        MusicLibraryProcessor processor(inputDirectoryPath);
        processor.traverseMusicLibrary();
        songs = processor.getSongs();
        return true;
    } else {
        std::cerr << "Error: The specified path does not exist or is not a directory." << std::endl;
        return false;
    }
}


void ApplicationController::run() {
    std::cout << "Working with "<< this->songs.size() << " songs" << std::endl;
    std::vector<std::shared_ptr<Track>> res;
    for (const auto& song : songs) {
        std::cout << "======================="<< std::endl;
        std::cout << "fileName: " << song.fileName << std::endl;
        std::cout << "title: " << song.title << std::endl;
        std::cout << "artist: " << song.artist << std::endl;
        std::cout << "album: "<< song.album << std::endl;
        std::cout << "genre: " << song.genre << std::endl;
        std::cout << "year: " << song.year << std::endl;
        std::cout << "duration: " << song.duration << std::endl;
        std::cout << "trackNumber: " << song.trackNumber << std::endl;

        auto rec = spotify.getRecommendations({}, {spotify.getTrack(song.title, song.artist).GetId()}, 1);
        res.push_back(rec[0]);
    }
    Track finalResult = spotify.getRecommendation(res);

    std::cout << finalResult.GetName() << std::endl;
    std::cout << finalResult.GetArtists()[0]->GetName() << std::endl;
    std::cout << finalResult.GetAlbum()->GetName() << std::endl;
}