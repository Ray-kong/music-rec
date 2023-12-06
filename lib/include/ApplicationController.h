//
// Created by Ray Kong on 12/3/23.
//

#ifndef MUSIC_REC_APPLICATIONCONTROLLER_H
#define MUSIC_REC_APPLICATIONCONTROLLER_H
#include "string"
#include "Song.h"
#include "SpotifyClient.h"
#include <vector>

class ApplicationController {
public:
    bool setUp(std::string inputDirectoryPath, std::string clientID, std::string clientSecret);
    void run();

private:
    std::vector<Song> songs;
    SpotifyClient spotify;
};


#endif //MUSIC_REC_APPLICATIONCONTROLLER_H
