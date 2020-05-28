//
// Created by Lou Zeh on 5/20/20.
//

#include "../include/spotify/song_listens.h"

#include <utility>

namespace spotify {

// helper methods

vector<SongListen> ParseJson(const vector<json> &songs) {
  vector<SongListen> vec;
  for (json j: songs) {
    Song song(j["trackName"].get<string>(), j["artistName"].get<string>());
    SongListen song_listen(song, j["msPlayed"].get<long>(), j["endTime"].get<string>());
    vec.push_back(song_listen);
  }
  return vec;
}

vector<SongTotalListens> SortSongsByMs(const vector<SongListen> &song_listens) {
  vector<SongTotalListens> to_return;
  
  map<Song, long>::iterator itr;
  map<Song, long> all_song_listens = GetSongsToTotalMs(song_listens);
  
  for (itr = all_song_listens.begin(); itr != all_song_listens.end(); ++itr) {
    SongTotalListens song(itr->first, itr->second);
    to_return.push_back(song);
  }
  // kinda from:
  // https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
  sort(to_return.begin(), to_return.end(), [](const SongTotalListens& lhs, const SongTotalListens& rhs) {
    return lhs.total_milliseconds_listened > rhs.total_milliseconds_listened;
  });
  return to_return;
}

map<Song, long> GetSongsToTotalMs(const vector<SongListen>& song_listens) {
  map<Song, long> to_return;
  for (const SongListen& song_listen : song_listens) {
    // ty stackoverflow
    // https://stackoverflow.com/questions/60107054/c-equivalent-to-java-map-getordefault
    auto element = to_return.emplace(song_listen.song, song_listen.milliseconds_listened);
    // if nothing was emplaced
    if (!element.second) {
      element.first->second += song_listen.milliseconds_listened;
    }
  }
  return to_return;
}

// constructors

SongTotalListens::SongTotalListens(const SongListen &song_listen) {
  song = song_listen.song;
  total_milliseconds_listened = song_listen.milliseconds_listened;
  times_listened = 1;
}

SongTotalListens::SongTotalListens(const Song& set_song, long set_ms) {
  song = set_song;
  total_milliseconds_listened = set_ms;
  times_listened = 1;
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

// operator overloads

bool Song::operator==(const Song &song) const {
  return artist == song.artist && name == song.name;
}

bool SongTotalListens::operator<(const SongTotalListens &song_total_listens) const {
  return (total_milliseconds_listened < song_total_listens.total_milliseconds_listened);
}

bool SongListen::operator<(const SongListen &song_listen) const {
  return (milliseconds_listened < song_listen.milliseconds_listened);
}

bool SongListen::operator==(const SongListen &song_listen) const {
  return song == song_listen.song && time == song_listen.time
         && milliseconds_listened == song_listen.milliseconds_listened;
}

std::ostream& operator<<(std::ostream& os, const SongTotalListens& s)
{
  // again stolen from stackoverflow
  // https://stackoverflow.com/questions/50727304/convert-milliseconds-to-hoursminutessecondsmilliseconds-in-c
  long milli = s.total_milliseconds_listened;
  //3600000 milliseconds in an hour
  long hr = milli / 3600000;
  milli = milli - 3600000 * hr;
  //60000 milliseconds in a minute
  long min = milli / 60000;
  milli = milli - 60000 * min;
  //1000 milliseconds in a second
  long sec = milli / 1000;
  milli = milli - 1000 * sec;
  
  return os << s.song.name << " by " << s.song.artist << ": " << hr << " hr, "
    << min << " min, " << sec << " sec, " << milli << " ms";
}

std::ostream& operator<<(std::ostream& os, const SongListen& s) {
  return os << s.song.name << " by " << s.song.artist << " at " << s.time << ": " << s.milliseconds_listened;
}

std::ostream& operator<<(std::ostream& os, const Song& s) {
  return os << s.name << " by " << s.artist;
}

bool Song::operator<(const Song& song) const {
  return name < song.name;
}
}
