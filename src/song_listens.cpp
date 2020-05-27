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

vector<SongTotalListens> SortSongs(const vector<SongListen> &song_listens) {
  vector<SongTotalListens> vec;
  vector<vector<SongListen> > songs_together = DivideBySong(song_listens);
  
  return vec;
}


// i *know* this is like O(n^2) but i couldn't think of a better way so
vector<vector<SongListen> > DivideBySong(vector<SongListen> song_listens) {
  vector<vector<SongListen> > to_return;
  int j = 0;
  while (!song_listens.empty()) {
    cout << j << endl;
    int i = 0;
    SongListen first = song_listens[0];
    song_listens.erase(song_listens.begin());
    vector<SongListen> current_songs;
    current_songs.push_back(first);
    for (const SongListen& song_listen : song_listens) {
      if (song_listen.song == first.song) {
        current_songs.push_back(song_listen);
        song_listens.erase(song_listens.begin() + i);
      } else {
        i++;
      }
    }
    to_return.push_back(current_songs);
    j++;
  }
  return to_return;
}

vector<vector<SongListen> > DivideByArtist(vector<SongListen> song_listens) {

}

// constructors

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
  return os << s.song.name << " by " << s.song.artist << ": " << s.total_milliseconds_listened;
}

std::ostream& operator<<(std::ostream& os, const SongListen& s) {
  return os << s.song.name << " by " << s.song.artist << " at " << s.time << ": " << s.milliseconds_listened;
}
}
