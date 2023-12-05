//
// Created by Ray Kong on 12/3/23.
//

#include "../include/ApplicationController.h"
#include "../include/MusicLibraryProcessor.h"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

bool ApplicationController::setUp(std::string inputDirectoryPath) {
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
    for (const auto& song : songs) {
        std::cout << "Song: " << std::endl;
        std::cout << song.title << std::endl;
        std::cout << song.artist << std::endl;
        std::cout << song.album << std::endl;
        std::cout << song.genre << std::endl;
        std::cout << "======================="<< std::endl;
    }
}