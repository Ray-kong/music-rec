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

void SpotifyClient::setAuthentication(std::string clientID, std::string clientSecret) {
    this->clientID = clientID;
    this->clientSecret = clientSecret;
    requestAuthorization();
}

void SpotifyClient::requestAuthorization() {
    auto res = cpr::Post(cpr::Url{"https://accounts.spotify.com/api/token"},
                         cpr::Payload{{"grant_type", "client_credentials"},
                                      {"client_id", clientID},
                                      {"client_secret", clientSecret}});
    std::cout << clientID << std::endl;
    std::cout << clientSecret << std::endl;
    std::cout << res.text << std::endl;
    glz::json_t data;
    glz::read_json(data, res.text);
    accessToken = data["access_token"].get<std::string>();
    api.setAuthToken(accessToken);
}

Artist SpotifyClient::getArtist(const std::string &name) {
    auto res = api.SearchArtists(name);
    return res.GetItems()[0];
}

Track SpotifyClient::getTrack(const std::string &trackName, const std::string& artistName) {
    auto res = api.SearchTracks("track:" + trackName + " artist:" + artistName);
    if (res.GetTotal() < 1) {
        throw std::runtime_error("didn't get any results from getTrack");
    }
    return res.GetItems()[0];
}

// TODO: improve this API to allow for better use of data for recommendations
// Note: only allows 5 total artists + tracks (eg. 5 artists 0 tracks, 2 artists 3 tracks, etc)
std::vector<std::shared_ptr<Track>> SpotifyClient::getRecommendations(std::vector<std::string> artistIDs, std::vector<std::string> trackIDs, int count) {
    if (artistIDs.size() + trackIDs.size() > 5) {
        throw std::runtime_error("Too many seed artists and seed tracks");
    }
    if (count > 100 || count < 1) {
        throw std::runtime_error("recommendation count must be between 1 and 100");
    }
    // turn vectors into comma separated lists of seed values
    std::string seedArtists;
    std::string seedTracks;
    for (const std::string& artist : artistIDs) {
        seedArtists += artist + ",";
    }
    for (const std::string& track : trackIDs) {
        seedTracks += track + ",";
    }

    std::map<std::string, std::string> options;
    options["seed_artists"] = seedArtists;
    options["seed_tracks"] = seedTracks;
    options["market"] = "US";
    options["limit"] = std::to_string(count);
    // could potentially use other options to get a better recommendation list
    return api.GetRecommendations(options).GetTracks();
}

// Note: this algorithm recursively reduces the size of the list by 5 using the previous list to rerun the algorithm
// this process may not be optimal to retain the original spirit of the tracks
Track SpotifyClient::getRecommendation(const std::vector<std::shared_ptr<Track>>& tracks) {
    if (tracks.empty()) {
        throw std::runtime_error("missing seed tracks for recommendation");
    } else if (tracks.size() == 1) {
        return *tracks[0];
    }

    std::vector<std::shared_ptr<Track>> res;

    // loop over tracks in blocks of 5
    for (int i = 0; i < (tracks.size() + 4) / 5; i++) {
        std::vector<std::string> trackIDs;
        // turn 5 tracks into track ids
        for (int j = i * 5; j < tracks.size() && j < (i + 1) * 5; j++) {
            trackIDs.push_back(tracks[j]->GetId());
        }
        auto tempRes = getRecommendations({}, trackIDs);
        res.push_back(tempRes[0]);
    }

    // make recursive calls until only 1 track remains
    return getRecommendation(res);
}


