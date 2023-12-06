//
// Created by Ray Kong on 12/4/23.
//

#include "../include/MusicLibraryProcessor.h"
#include "AudioFile.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>



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
    return extension == ".wav"; //TODO: Add more extensions as necessary
}

Song MusicLibraryProcessor::extractMetadata(const std::string& filePath) {
    Song song = {};
    std::filesystem::path filePathObj(filePath);
    song.fileName = filePathObj.filename().string();
    // Create an input file stream in binary mode to read from the file at filePath
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return song;
    }

    // Declare a buffer of 4 bytes for reading 4-byte headers and identifiers from the file
    char buffer[4];
    // Check if reading the first 4 bytes failed or if they do not match the 'RIFF' header of a WAV file
    if (!file.read(buffer, 4) || strncmp(buffer, "RIFF", 4) != 0) {
        std::cerr << "Not a valid WAV file\n";
        return song;
    }

    file.seekg(4, std::ios::cur); // Skip file size

    file.read(buffer, 4); // Read 'WAVE' header
    if (strncmp(buffer, "WAVE", 4) != 0) {
        std::cerr << "Not a valid WAV format\n";
        return song;
    }

    int sampleRate = 0, byteRate = 0, dataSize = 0;
    while (file.read(buffer, 4)) {
        int size;
        // Read the next bytes (size of the chunk) from the file directly into the 'size' variable
        file.read(reinterpret_cast<char *>(&size), sizeof(size));

        if (strncmp(buffer, "fmt ", 4) == 0) {
            int16_t audioFormat, numChannels, blockAlign, bitsPerSample;
            // Read the next bytes (header of the fmt chunk) from the file directly into the corresponding variables
            file.read(reinterpret_cast<char *>(&audioFormat), sizeof(audioFormat));
            file.read(reinterpret_cast<char *>(&numChannels), sizeof(numChannels));
            file.read(reinterpret_cast<char *>(&sampleRate), sizeof(sampleRate));
            file.read(reinterpret_cast<char *>(&byteRate), sizeof(byteRate));
            file.read(reinterpret_cast<char *>(&blockAlign), sizeof(blockAlign));
            file.read(reinterpret_cast<char *>(&bitsPerSample), sizeof(bitsPerSample));
            file.seekg(size - 16, std::ios::cur);  // Skip remaining bytes in fmt chunk
        } else if (strncmp(buffer, "data", 4) == 0) {
            dataSize = size;
            file.seekg(size, std::ios::cur);  // Skip data chunk
        } else if (strncmp(buffer, "LIST", 4) == 0) {
            int listEnd = static_cast<int>(file.tellg()) + size;
            file.read(buffer, 4);  // Read type of LIST chunk (should be "INFO")

            // Read sub-chunks of LIST chunk
            while (file.tellg() < listEnd) {
                file.read(buffer, 4);  // Read sub-chunk ID
                int subChunkSize;
                file.read(reinterpret_cast<char *>(&subChunkSize), sizeof(subChunkSize));

                std::string metadata(subChunkSize, '\0');
                file.read(&metadata[0], subChunkSize);

                // Remove null characters from the end of the string
                metadata.erase(std::find(metadata.begin(), metadata.end(), '\0'), metadata.end());

                if (strncmp(buffer, "INAM", 4) == 0) {
                    song.title = metadata;
                } else if (strncmp(buffer, "IART", 4) == 0) {
                    song.artist = metadata;
                } else if (strncmp(buffer, "IPRD", 4) == 0) {
                    song.album = metadata;
                } else if (strncmp(buffer, "IGNR", 4) == 0) {
                    song.genre = metadata;
                } else if (strncmp(buffer, "ICRD", 4) == 0) {
                    song.year = metadata;
                } else if (strncmp(buffer, "ITRK", 4) == 0) {
                    song.trackNumber = stoi(metadata);
                }

                // Align to even number of bytes (sub-chunk size + padding)
                if (subChunkSize % 2 == 1) {
                    file.seekg(1, std::ios::cur);
                }
            }
        } else {
            file.seekg(size, std::ios::cur);  // Skip unknown chunks
        }
    }

    if (sampleRate > 0 && byteRate > 0) {
        song.duration = static_cast<double>(dataSize) / byteRate;
    }

    return song;
}