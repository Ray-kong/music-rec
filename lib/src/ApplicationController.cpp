//
// Created by Ray Kong on 12/3/23.
//

#include "../include/ApplicationController.h"
#include "../include/MusicLibraryProcessor.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool ApplicationController::setUp(std::string inputDirectoryPath) {
    if (fs::exists(inputDirectoryPath) && fs::is_directory(inputDirectoryPath)) {
        this->songs = MusicLibraryProcessor(inputDirectoryPath).getSongs();
        return true;
    } else {
        std::cerr << "Error: The specified path does not exist or is not a directory." << std::endl;
        return false;
    }
}


void ApplicationController::run() {
    std::cout << this->songs.size() << std::endl;
}