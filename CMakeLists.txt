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

# http requests library
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8 # The commit hash for 1.10.x.
        # Replace with the latest from: https://github.com/libcpr/cpr/releases
)

# updated json library
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# replace the spotify library's json dependency with a newer version
set(replace_json cp ${json_SOURCE_DIR}/single_include/nlohmann/json.hpp src/utils/json.h)

FetchContent_Declare(
        spotify
        GIT_REPOSITORY https://github.com/smaltby/spotify-api-plusplus.git
        PATCH_COMMAND ${replace_json}
)

FetchContent_Declare(
        glaze
        GIT_REPOSITORY https://github.com/stephenberry/glaze.git
        GIT_TAG main
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(AudioFile Gist cpr spotify glaze)

# fix spotify type error
file(READ ${spotify_SOURCE_DIR}/src/utils/CurlUtils.h FILE_CONTENTS)
string(REPLACE "return curl;" "return {};" FILE_CONTENTS "${FILE_CONTENTS}")
file(WRITE ${spotify_SOURCE_DIR}/src/utils/CurlUtils.h "${FILE_CONTENTS}")

# Include the Gist src directory
include_directories(${gist_SOURCE_DIR}/src)
# Include the taglib directory
include_directories(${taglib_SOURCE_DIR}/taglib)
# include the spotify directory
include_directories(${spotify_SOURCE_DIR}/src)

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
        lib/src/SpotifyClient.cpp
        lib/include/SpotifyClient.h
)

# Link the fetched dependencies with the target
#TODO: add taglib
target_link_libraries(music_rec PRIVATE AudioFile cpr::cpr spotify-api-plusplus glaze::glaze)

# Set the C++ standard
set_target_properties(music_rec PROPERTIES CXX_STANDARD 17)
