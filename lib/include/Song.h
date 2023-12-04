//
// Created by Ray Kong on 12/3/23.
//

#ifndef SONG_H
#define SONG_H

#include <string>

struct Song {
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    // Add other metadata fields as necessary

    // Constructor
    Song(const std::string& title, const std::string& artist,
         const std::string& album, const std::string& genre)
            : title(title), artist(artist), album(album), genre(genre) {}

    // You can still add methods here if needed
};

#endif // SONG_H
