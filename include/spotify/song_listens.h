//
// Created by Lou Zeh on 5/20/20.
//

#ifndef SPOTIFY_SONG_LISTENS_H
#define SPOTIFY_SONG_LISTENS_H

#include <string>
#include <iostream>
#include "nlohmann/json.hpp"

using std::string;
using std::vector;
using std::map;
using std::pair;

using std::max_element;
using std::sort;

using std::cout;
using std::endl;

using json = nlohmann::json;

namespace spotify {

struct Song {
  string name;
  string artist;
  Song(string set_name, string set_artist);
  Song();
  bool operator==(const Song& song) const;
  bool operator<(const Song& song) const;
};

struct SongListen {
  Song song;
  long milliseconds_listened;
  string time;
  SongListen(Song set_song, long set_ms, string set_time);
  bool operator<(const SongListen& song_listen) const;
  bool operator==(const SongListen& song_listen) const;
};

struct SongTotalListens {
  explicit SongTotalListens(const SongListen& song_listen);
  SongTotalListens(const Song& set_song, long set_ms);
  Song song;
  long total_milliseconds_listened;
  int times_listened;
  bool operator<(const SongTotalListens& song_total_listens) const;
};

struct ArtistTotalListens {
  ArtistTotalListens(const string& set_artist, long set_ms);
  string artist;
  long total_milliseconds_listened;
};

vector<SongListen> ParseJson(const vector<json>& songs);

vector<SongTotalListens> SortSongsByMs(const vector<SongListen>& song_listens);

vector<ArtistTotalListens> SortArtistsByMs(const vector<SongListen>& song_listens);

map<Song, long> GetSongsToTotalMs(const vector<SongListen>& song_listens);

map<Song, int> GetSongsToTotalPlays(const vector<SongListen>& song_listens);

map<string, long> GetArtistToTotalMs(const vector<SongListen>& song_listens);

std::ostream& operator<<(std::ostream& os, const SongTotalListens& s);

std::ostream& operator<<(std::ostream& os, const ArtistTotalListens& a);

std::ostream& operator<<(std::ostream& os, const SongListen& s);

std::ostream& operator<<(std::ostream& os, const Song& s);

}



#endif //SPOTIFY_SONG_LISTENS_H
