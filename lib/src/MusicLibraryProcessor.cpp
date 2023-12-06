//
// Created by Ray Kong on 12/4/23.
//

#include "../include/MusicLibraryProcessor.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>


MusicLibraryProcessor::MusicLibraryProcessor(const std::string& path)
        : musicLibraryPath(path) {}

void MusicLibraryProcessor::traverseMusicLibrary() {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(musicLibraryPath)) {
        if (!entry.is_directory() && isMusicFile(entry.path().extension().string())) {
            Song song = extractMetadata(entry.path().string());
            songs.push_back(song);
        }
    }
}

const std::vector<Song>& MusicLibraryProcessor::getSongs() const {
    return songs;
}

bool MusicLibraryProcessor::isMusicFile(const std::string& extension) {
    return extension == ".mp3"; //TODO: Add more extensions as necessary
}

Song MusicLibraryProcessor::extractMetadata(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    std::filesystem::file_size(filePath);

    if (!file) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    if (fileSize < 128) {
        throw std::runtime_error("Invalid MP3 file: " + filePath);
    }

    file.seekg(static_cast<std::streamoff>(fileSize) - 128);

    char buffer[128];
    file.read(buffer, 128);

    if (std::string(buffer, 3) != "TAG") {
        //throw std::runtime_error("Invalid MP3 metadata: " + filePath);
        std::cout << "Invalid MP3 metadata: " << filePath << std::endl;
    }

    std::filesystem::path fsPath(filePath);
    return {
            fsPath.stem().string(),  // Placeholder for actual title extraction
            std::string(buffer + 3, 30),  // Extracting artist
            std::string(buffer + 33, 30), // Extracting album
            std::string(buffer + 127, 1)  // Extracting genre
    };
}
