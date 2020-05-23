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
  Song(string set_name, string set_artist);
  Song();
};

struct SongListen {
  Song song;
  long milliseconds_listened;
  string time;
  SongListen(Song set_song, long set_ms, string set_time);
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

std::ostream& operator<<(std::ostream& os, const SongTotalListens& s);

}



#endif //SPOTIFY_SONG_LISTENS_H
