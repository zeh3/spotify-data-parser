//
// Created by Lou Zeh on 5/20/20.
//

#ifndef SPOTIFY_SONG_LISTENS_H
#define SPOTIFY_SONG_LISTENS_H

#include <string>
#include <iostream>
#include "nlohmann/json.hpp"



namespace spotify {

struct Song {
  std::string name;
  std::string artist;
  Song(std::string set_name, std::string set_artist);
  Song();
  bool operator==(const Song& song) const;
  bool operator<(const Song& song) const;
};

struct Plays {
  Plays(long set_sec, int set_times);
  Plays();
  long seconds_listened;
  int times_listened;
};

struct SongListen {
  Song song;
  long milliseconds_listened;
  std::string time;
  SongListen(Song set_song, long set_ms, std::string set_time);
  bool operator<(const SongListen& song_listen) const;
  bool operator==(const SongListen& song_listen) const;
};

struct SongTotalListens {
  explicit SongTotalListens(const SongListen& song_listen);
  SongTotalListens(const Song& set_song, Plays set_plays);
  Song song;
  Plays plays;
  bool operator<(const SongTotalListens& song_total_listens) const;
};

struct ArtistTotalListens {
  ArtistTotalListens(const std::string& set_artist, Plays set_plays);
  std::string artist;
  Plays plays;
};



std::vector<SongListen> ParseJson(const std::vector<nlohmann::json>& songs);

std::vector<SongTotalListens> SortSongsByTime(const std::vector<SongListen>& song_listens);

std::vector<ArtistTotalListens> SortArtistsByTime(const std::vector<SongListen>& song_listens);

std::vector<SongTotalListens> SortSongsByPlays(const std::vector<SongListen>& song_listens);

std::vector<ArtistTotalListens> SortArtistsByPlays(const std::vector<SongListen>& song_listens);

std::map<Song, Plays> GetSongsToTotalSec(const std::vector<SongListen>& song_listens);

std::map<std::string, Plays> GetArtistToTotalSec(const std::vector<SongListen>& song_listens);

std::vector<std::vector<SongTotalListens> > GetSortedSongsByArtist(const std::vector<SongListen>& song_listens);

std::map<std::string, std::vector<SongTotalListens> > MapArtistsToSongs(const std::vector<SongListen>& song_listens);

std::ostream& operator<<(std::ostream& os, const SongTotalListens& s);

std::ostream& operator<<(std::ostream& os, const ArtistTotalListens& a);

std::ostream& operator<<(std::ostream& os, const SongListen& s);

std::ostream& operator<<(std::ostream& os, const Song& s);

}



#endif //SPOTIFY_SONG_LISTENS_H
