//
// Created by Ray Kong on 12/4/23.
//

#include "../include/MusicLibraryProcessor.h"

MusicLibraryProcessor::MusicLibraryProcessor(const std::string& path)
        : musicLibraryPath(path) {}

void MusicLibraryProcessor::traverseMusicLibrary() {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(musicLibraryPath)) {
        if (!entry.is_directory() && isMusicFile(entry.path().string())) {
            Song song = extractMetadata(entry.path().string());
            songs.push_back(song);
        }
    }
}

const std::vector<Song>& MusicLibraryProcessor::getSongs() const {
    return songs;
}

bool MusicLibraryProcessor::isMusicFile(const std::string& filePath) {
    size_t pos = filePath.find_last_of(".");
    std::string ext = filePath.substr(pos + 1);
    return ext == "wav" || ext == "mp3"; // Add more extensions as necessary
}

Song MusicLibraryProcessor::extractMetadata(const std::string& filePath) {

    return Song("Dummy Title", "Dummy Artist", "Dummy Album", "Dummy Genre");
}
