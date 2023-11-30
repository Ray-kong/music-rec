cmake_minimum_required(VERSION 3.20)
project(music_rec)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        taglib
        GIT_REPOSITORY https://github.com/taglib/taglib.git
)

FetchContent_Declare(
        AudioFile
        GIT_REPOSITORY https://github.com/adamstark/AudioFile.git
)

FetchContent_MakeAvailable(AudioFile taglib)

add_executable(music_rec main.cpp)
target_link_libraries(music_rec AudioFile taglib)
