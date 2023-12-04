//
// Created by Ray Kong on 12/3/23.
//

#ifndef MUSIC_REC_APPLICATIONCONTROLLER_H
#define MUSIC_REC_APPLICATIONCONTROLLER_H
#include "string"
#include "Song.h"
#include <vector>

class ApplicationController {
public:
    std::vector<Song> songs;
    bool setUp(std::string inputDirectoryPath);
    void run();

private:

};


#endif //MUSIC_REC_APPLICATIONCONTROLLER_H
