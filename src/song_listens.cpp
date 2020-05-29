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
  
  map<Song, Plays>::iterator itr;
  map<Song, Plays> all_song_listens = GetSongsToTotalMs(song_listens);
  
  for (itr = all_song_listens.begin(); itr != all_song_listens.end(); ++itr) {
    SongTotalListens song(itr->first, itr->second);
    to_return.push_back(song);
  }
  // kinda from:
  // https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
  sort(to_return.begin(), to_return.end(), [](const SongTotalListens& lhs, const SongTotalListens& rhs) {
    return lhs.plays.milliseconds_listened > rhs.plays.milliseconds_listened;
  });
  return to_return;
}

vector<SongTotalListens> SortSongsByPlays(const vector<SongListen>& song_listens) {
  vector<SongTotalListens> songs = SortSongsByMs(song_listens);
  sort(songs.begin(), songs.end(), [](const SongTotalListens& lhs, const SongTotalListens& rhs) {
    return lhs.plays.times_listened > rhs.plays.times_listened;
  });
  return songs;
}


map<Song, Plays> GetSongsToTotalMs(const vector<SongListen>& song_listens) {
  map<Song, Plays> to_return;
  for (const SongListen& song_listen : song_listens) {
    // ty stackoverflow
    // https://stackoverflow.com/questions/60107054/c-equivalent-to-java-map-getordefault
    auto element = to_return.emplace(song_listen.song, Plays(song_listen.milliseconds_listened, 1));
    // if nothing was emplaced
    if (!element.second) {
      element.first->second.milliseconds_listened += song_listen.milliseconds_listened;
      element.first->second.times_listened++;
    }
  }
  return to_return;
}

vector<ArtistTotalListens> SortArtistsByMs(const vector<SongListen>& song_listens) {
  vector<ArtistTotalListens> to_return;
  
  map<string, Plays>::iterator itr;
  map<string, Plays> all_artist_listens = GetArtistToTotalMs(song_listens);
  
  for (itr = all_artist_listens.begin(); itr != all_artist_listens.end(); ++itr) {
    ArtistTotalListens artist(itr->first, itr->second);
    to_return.push_back(artist);
  }
  // kinda from:
  // https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
  sort(to_return.begin(), to_return.end(), [](const ArtistTotalListens& lhs, const ArtistTotalListens& rhs) {
    return lhs.plays.milliseconds_listened > rhs.plays.milliseconds_listened;
  });
  return to_return;
}

vector<ArtistTotalListens> SortArtistsByPlays(const vector<SongListen>& song_listens) {
  vector<ArtistTotalListens> artists = SortArtistsByMs(song_listens);
  sort(artists.begin(), artists.end(), [](const ArtistTotalListens& lhs, const ArtistTotalListens& rhs) {
    return lhs.plays.times_listened > rhs.plays.times_listened;
  });
  return artists;
}

map<string, Plays> GetArtistToTotalMs(const vector<SongListen>& song_listens) {
  map<string, Plays> to_return;
  for (const SongListen& song_listen : song_listens) {
    // ty stackoverflow
    // https://stackoverflow.com/questions/60107054/c-equivalent-to-java-map-getordefault
    auto element = to_return.emplace(song_listen.song.artist, Plays(song_listen.milliseconds_listened, 1));
    // if nothing was emplaced
    if (!element.second) {
      element.first->second.milliseconds_listened += song_listen.milliseconds_listened;
      element.first->second.times_listened++;
    }
  }
  return to_return;
}

vector<vector<SongTotalListens> > GetSortedSongsByArtist(const vector<SongListen>& song_listens) {
  vector<vector<SongTotalListens> > to_return;
  map<string, vector<SongTotalListens> > artist_to_songs = MapArtistsToSongs(song_listens);
  vector<ArtistTotalListens> sorted_artists = SortArtistsByMs(song_listens);
  
  to_return.reserve(sorted_artists.size());
  for (const ArtistTotalListens& artist_listen: sorted_artists) {
    
    try {
      to_return.push_back(artist_to_songs.at(artist_listen.artist));
    } catch(exception e) {
      cout << artist_listen.artist << endl;
    }
    
  }
  
  return to_return;
}

map<string, vector<SongTotalListens> > MapArtistsToSongs(const vector<SongListen>& song_listens) {
  vector<SongTotalListens> song_total_listens = SortSongsByMs(song_listens);
  map<string, vector<SongTotalListens> > to_return;
  
  for (const SongTotalListens& song_total_listen : song_total_listens) {
    // ty stackoverflow
    // https://stackoverflow.com/questions/60107054/c-equivalent-to-java-map-getordefault
    vector<SongTotalListens> vec;
    vec.push_back(song_total_listen);
    auto element = to_return.emplace(song_total_listen.song.artist, vec);
    // if nothing was emplaced
    if (!element.second) {
      element.first->second.push_back(song_total_listen);
    }
  }
  
  return to_return;
}

// constructors

Plays::Plays(long set_ms, int set_times) {
  milliseconds_listened = set_ms;
  times_listened = set_times;
}

ArtistTotalListens::ArtistTotalListens(const string &set_artist, Plays set_plays) {
  artist = set_artist;
  plays = set_plays;
}

SongTotalListens::SongTotalListens(const SongListen &song_listen) {
  song = song_listen.song;
  plays.milliseconds_listened = song_listen.milliseconds_listened;
  plays.times_listened = 1;
}

SongTotalListens::SongTotalListens(const Song& set_song, Plays set_plays) {
  song = set_song;
  plays = set_plays;
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

Plays::Plays() {
  // ditto lol
}

// operator overloads

bool Song::operator==(const Song &song) const {
  return artist == song.artist && name == song.name;
}

bool SongTotalListens::operator<(const SongTotalListens &song_total_listens) const {
  return (plays.milliseconds_listened < song_total_listens.plays.milliseconds_listened);
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
  long milli = s.plays.milliseconds_listened;
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
  return name + artist < song.name + song.artist;
}

std::ostream& operator<<(std::ostream& os, const ArtistTotalListens& a) {
  // again stolen from stackoverflow
  // https://stackoverflow.com/questions/50727304/convert-milliseconds-to-hoursminutessecondsmilliseconds-in-c
  long milli = a.plays.milliseconds_listened;
  //3600000 milliseconds in an hour
  long hr = milli / 3600000;
  milli = milli - 3600000 * hr;
  //60000 milliseconds in a minute
  long min = milli / 60000;
  milli = milli - 60000 * min;
  //1000 milliseconds in a second
  long sec = milli / 1000;
  milli = milli - 1000 * sec;
  
  return os << a.artist << ": " << hr << " hr, "
            << min << " min, " << sec << " sec, " << milli << " ms";
}

}
