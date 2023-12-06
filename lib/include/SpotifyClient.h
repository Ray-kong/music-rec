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
    SpotifyClient() = default;

    void setAuthentication(std::string clientID, std::string clientSecret);
    Artist getArtist(const std::string& name);
    Track getTrack(const std::string& trackName, const std::string& artistName);
    // get many
    std::vector<std::shared_ptr<Track>> getRecommendations(std::vector<std::string> artistIDs, std::vector<std::string> trackIDs, int count = 20);
    // reduce a list of tracks down to a single recommendation
    Track getRecommendation(const std::vector<std::shared_ptr<Track>>& tracks);

private:
    // storage for tokens and ids
    std::string clientID;
    std::string clientSecret;
    std::string accessToken;
    // spotify library client
    SpotifyAPI api;

    // execute oauth flow
    void requestAuthorization();
};


#endif //MUSIC_REC_SPOTIFYCLIENT_H
