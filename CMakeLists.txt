cmake_minimum_required(VERSION 3.20)
project(music_rec)

set(CMAKE_CXX_STANDARD 17)

# Include FetchContent
include(FetchContent)
set(ignore_tests echo "" > tests/CMakeLists.txt)

# Fetch and make available the required dependencies
FetchContent_Declare(
        taglib
        GIT_REPOSITORY https://github.com/taglib/taglib.git
        PATCH_COMMAND ${ignore_tests}
)

FetchContent_Declare(
        AudioFile
        GIT_REPOSITORY https://github.com/adamstark/AudioFile.git
        PATCH_COMMAND ${ignore_tests}
)

FetchContent_Declare(
        Gist
        GIT_REPOSITORY https://github.com/adamstark/Gist.git
        PATCH_COMMAND ${ignore_tests}
)

FetchContent_MakeAvailable(AudioFile Gist)

add_executable(music_rec main.cpp
        lib/include/Song.h
        lib/src/ApplicationController.cpp
        lib/include/ApplicationController.h
        lib/include/ApplicationController.h
        lib/src/ApplicationController.cpp
        lib/include/ApplicationController.h
        lib/src/Song.cpp
        lib/include/Song.h
        lib/include/Song.h
        lib/src/ApplicationController.cpp
        lib/src/MusicLibraryProcessor.cpp
        lib/include/MusicLibraryProcessor.h
)

# Link the fetched dependencies with the target
#TODO: add taglib
target_link_libraries(music_rec PRIVATE  AudioFile Gist)

# Set the C++ standard
set_target_properties(music_rec PROPERTIES CXX_STANDARD 17)
