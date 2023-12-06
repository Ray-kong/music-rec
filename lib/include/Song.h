//
// Created by Ray Kong on 12/3/23.
//

#ifndef SONG_H
#define SONG_H

#include <string>

struct Song {
    std::string fileName;
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    std::string year;
    double duration;
    int trackNumber;

};

#endif // SONG_H
