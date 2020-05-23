//
// Created by Lou Zeh on 5/20/20.
//

#include "../include/spotify/song_listens.h"

#include <utility>

namespace spotify {
vector<SongListen> ParseJson(const vector<json> &songs) {
  vector<SongListen> vec;
  for (json j: songs) {
    Song song(j["trackName"].get<string>(), j["artistName"].get<string>());
    SongListen song_listen(song, j["msPlayed"].get<long>(), j["endTime"].get<string>());
    vec.push_back(song_listen);
  }
  return vec;
}

vector<SongTotalListens> SortSongs(const vector<SongListen> &song_listens) {
  vector<SongTotalListens> vec;
  return vec;
}

std::ostream& operator<<(std::ostream& os, const SongTotalListens& s)
{
  return os << s.song.name << " by " << s.song.artist << ": " << s.total_milliseconds_listened;
}

SongListen::SongListen(Song set_song, long set_ms, string set_time) {
  song = std::move(set_song);
  milliseconds_listened = set_ms;
  time = std::move(set_time);
}

Song::Song(string set_name, string set_artist) {
  name = std::move(set_name);
  artist = std::move(set_artist);
}

Song::Song() {
  //bc the SongListen constructor didn't like that Song didn't have a default constructor
}
}
