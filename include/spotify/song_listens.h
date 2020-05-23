//
// Created by Lou Zeh on 5/20/20.
//

#ifndef SPOTIFY_SONG_LISTENS_H
#define SPOTIFY_SONG_LISTENS_H

#include <string>
#include "nlohmann/json.hpp"

using std::string;
using std::vector;
using json = nlohmann::json;

namespace spotify {

struct Song {
  string name;
  string artist;
};

struct SongListen {
  Song song;
  long milliseconds_listened;
  string time;
};

struct SongTotalListens {
  Song song;
  long total_milliseconds_listened;
};

struct ArtistTotalListens {
  string artist;
  long total_milliseconds_listened;
};

vector<SongListen> ParseJson(const vector<json>& songs);

vector<SongTotalListens> SortSongs(const vector<SongListen>& song_listens);

}



#endif //SPOTIFY_SONG_LISTENS_H
