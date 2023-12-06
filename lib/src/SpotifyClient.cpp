//
// Created by Alexander Chang-Davidson on 12/5/23.
//

#include <algorithm>
#include "../include/SpotifyClient.h"
#include <glaze/json.hpp>
#include <iostream>

SpotifyClient::SpotifyClient(std::string clientID, std::string clientSecret)
    : clientID(std::move(clientID)), clientSecret(std::move(clientSecret)) {
    if (this->clientID.empty() || this->clientSecret.empty()) {
        throw std::runtime_error("Missing clientID or clientSecret");
    }
    requestAuthorization();
}

void SpotifyClient::requestAuthorization() {
    auto res = cpr::Post(cpr::Url{"https://accounts.spotify.com/api/token"},
                         cpr::Payload{{"grant_type", "client_credentials"},
                                      {"client_id", clientID},
                                      {"client_secret", clientSecret}});
    glz::json_t data;
    glz::read_json(data, res.text);
    accessToken = data["access_token"].get<std::string>();
    api.setAuthToken(accessToken);
}

Artist SpotifyClient::getArtist(const std::string &name) {
    auto res = api.SearchArtists(name);
    return res.GetItems()[0];
}

Track SpotifyClient::getTrack(const std::string &trackName) {
    auto res = api.SearchTracks(trackName);
    return res.GetItems()[0];
}

// TODO: improve this API to allow for better use of data for recommendations
// Note: only allows 5 total artists + tracks (eg. 5 artists 0 tracks, 2 artists 3 tracks, etc)
std::vector<std::shared_ptr<Track>> SpotifyClient::getRecommendations(std::vector<std::string> artists, std::vector<std::string> tracks) {
    if (artists.size() + tracks.size() > 5) {
        // note prioritizes artists over tracks
        if (artists.size() > 5) artists.resize(5);
        tracks.resize(5 - artists.size());
    }
    // turn vectors into comma separated lists of seed values
    std::string seedArtists;
    std::string seedTracks;
    for (const std::string& artist : artists) {
        seedArtists += getArtist(artist).GetId() + ",";
    }
    for (const std::string& track : tracks) {
        seedTracks += getTrack(track).GetId() + ",";
    }

    std::map<std::string, std::string> options;
    options["seed_artists"] = seedArtists;
    options["seed_tracks"] = seedTracks;
    options["market"] = "US";
    // could potentially use other options to get a better recommendation list
    return api.GetRecommendations(options).GetTracks();
}



