//
// Created by Ray Kong on 12/4/23.
//

#include "../include/MusicLibraryProcessor.h"

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
    return extension == ".wav" || extension == ".mp3"; //TODO: Add more extensions as necessary
}

Song MusicLibraryProcessor::extractMetadata(const std::string& filePath) {
    return {"Dummy Title", "Dummy Artist", "Dummy Album", "Dummy Genre"};
}
