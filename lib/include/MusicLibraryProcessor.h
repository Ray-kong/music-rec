//
// Created by Ray Kong on 12/4/23.
//

// MusicLibraryProcessor.h
#ifndef MUSICLIBRARYPROCESSOR_H
#define MUSICLIBRARYPROCESSOR_H

#include <vector>
#include <string>
#include <filesystem>
#include "Song.h"

class MusicLibraryProcessor {
public:
    MusicLibraryProcessor(const std::string& path);
    void traverseMusicLibrary();
    const std::vector<Song>& getSongs() const;

private:
    std::string musicLibraryPath;
    std::vector<Song> songs;

    bool isMusicFile(const std::string& extension);
    Song extractMetadata(const std::string& filePath);
};

#endif // MUSICLIBRARYPROCESSOR_H

