#include <iostream>
#include <vector>
#include <fstream>
#include "../include/spotify/song_listens.h"
#include "nlohmann/json.hpp"

using std::string;
using std::vector;
using namespace spotify;
using std::ifstream;
using std::cerr;
using std::endl;
using std::exception;
using std::ofstream;

vector<string> file_paths = {"MyData/StreamingHistory0.json", "MyData/StreamingHistory1.json",
                             "MyData/StreamingHistory2.json", "MyData/StreamingHistory3.json"};
string top_songs_by_play_time_path = "MyData/TopSongsMs.txt";
string top_songs_by_plays_path = "MyData/TopSongsPlays.txt";
string top_artists_by_play_time_path = "MyData/TopArtistsMs.txt";
string top_artists_by_plays_path = "MyData/TopArtistsPlays.txt";
string random_stats_path = "MyData/stats.txt";

int main() {
  vector<json> json_songs;
  
  for (const string& file_path : file_paths) {
    ifstream json_stream(file_path);
    string first;
    if (json_stream.fail()) {
      cerr << "invalid file path" << endl;
      return EXIT_FAILURE;
    }
    json json_songs_array;
    try {
      json_stream >> json_songs_array;
    } catch (exception& e) {
      cerr << "error parsing json" << endl;
      return EXIT_FAILURE;
    }
    vector<json> json_vector = json_songs_array.get<std::vector<json> >();
    // code for appending vectors taken from:
    // https://stackoverflow.com/questions/201718/concatenating-two-stdvectors
    json_songs.insert(json_songs.end(), json_vector.begin(), json_vector.end());
  }
  vector<SongListen> songs = ParseJson(json_songs);
  
  vector<SongTotalListens> sorted_songs_ms = SortSongsByMs(songs);
  ofstream top_songs_ms_file;
  top_songs_ms_file.open(top_songs_by_play_time_path);
  int i = 1;
  for (const SongTotalListens& song : sorted_songs_ms) {
    top_songs_ms_file << i << ": " << song << endl;
    i++;
  }
  
  vector<SongTotalListens> sorted_songs_plays = SortSongsByPlays(songs);
  ofstream top_songs_plays_file;
  top_songs_plays_file.open(top_songs_by_plays_path);
  i = 1;
  for (const SongTotalListens& song : sorted_songs_plays) {
    top_songs_plays_file << i << ": " << song.song << ": " << song.plays.times_listened << endl;
    i++;
  }
  
  vector<ArtistTotalListens> sorted_artists_ms = SortArtistsByMs(songs);
  ofstream top_artists_ms_file;
  top_artists_ms_file.open(top_artists_by_play_time_path);
  i = 1;
  for (const ArtistTotalListens& artist : sorted_artists_ms) {
    top_artists_ms_file << i << ": " << artist << endl;
    i++;
  }
  
  vector<ArtistTotalListens> sorted_artists_plays = SortArtistsByPlays(songs);
  ofstream top_artists_plays_file;
  top_artists_plays_file.open(top_artists_by_plays_path);
  i = 1;
  for (const ArtistTotalListens& artist : sorted_artists_plays) {
    top_artists_plays_file << i << ": " << artist.artist << ": " << artist.plays.times_listened << endl;
    i++;
  }
  
  return EXIT_SUCCESS;
}
