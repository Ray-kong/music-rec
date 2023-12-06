//
// Created by Alexander Chang-Davidson on 12/5/23.
//

#ifndef MUSIC_REC_SPOTIFYCLIENT_H
#define MUSIC_REC_SPOTIFYCLIENT_H

#include <string>
#include <cpr/cpr.h>
#include "SpotifyAPI.h"

class SpotifyClient {
public:
    SpotifyClient(std::string clientID, std::string clientSecret);

    Artist getArtist(const std::string& name);
    Track getTrack(const std::string& trackName);
    std::vector<std::shared_ptr<Track>> getRecommendations(std::vector<std::string> artists, std::vector<std::string> tracks);

private:
    // storage for tokens and ids
    const std::string clientID;
    const std::string clientSecret;
    std::string accessToken;
    // spotify library client
    SpotifyAPI api;

    void requestAuthorization();
};


#endif //MUSIC_REC_SPOTIFYCLIENT_H
