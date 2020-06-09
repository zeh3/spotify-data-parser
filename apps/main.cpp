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
using json = nlohmann::json;

const vector<string> file_paths = {"MyData/StreamingHistory0.json", "MyData/StreamingHistory1.json",
                             "MyData/StreamingHistory2.json", "MyData/StreamingHistory3.json"};
const string top_songs_by_play_time_path = "results/TopSongsTime.txt";
const string top_songs_by_plays_path = "results/TopSongsPlays.txt";
const string top_artists_by_play_time_path = "results/TopArtistsTime.txt";
const string top_artists_by_plays_path = "results/TopArtistsPlays.txt";
const string artists_breakdown_path = "results/ArtistsBreakdown.md";
const string random_stats_path = "results/stats.txt";

int main() {
  vector<json> json_songs;
  // json -> songs
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
  
  // TOP SONGS PLAY TIME
  vector<SongTotalListens> sorted_songs_ms = SortSongsByMs(songs);
  ofstream top_songs_ms_file;
  top_songs_ms_file.open(top_songs_by_play_time_path);
  int rank = 1;
  for (const SongTotalListens& song : sorted_songs_ms) {
    top_songs_ms_file << rank << ": " << song << endl;
    rank++;
  }
  
  // TOP SONGS PLAYS
  vector<SongTotalListens> sorted_songs_plays = SortSongsByPlays(songs);
  ofstream top_songs_plays_file;
  top_songs_plays_file.open(top_songs_by_plays_path);
  rank = 1;
  for (const SongTotalListens& song : sorted_songs_plays) {
    top_songs_plays_file << rank << ": " << song.song << ": " << song.plays.times_listened << endl;
    rank++;
  }
  
  // TOP ARTISTS PLAY TIME
  vector<ArtistTotalListens> sorted_artists_ms = SortArtistsByMs(songs);
  ofstream top_artists_ms_file;
  top_artists_ms_file.open(top_artists_by_play_time_path);
  rank = 1;
  for (const ArtistTotalListens& artist : sorted_artists_ms) {
    top_artists_ms_file << rank << ": " << artist << endl;
    rank++;
  }
  
  // TOP ARTISTS PLAYS
  vector<ArtistTotalListens> sorted_artists_plays = SortArtistsByPlays(songs);
  ofstream top_artists_plays_file;
  top_artists_plays_file.open(top_artists_by_plays_path);
  rank = 1;
  for (const ArtistTotalListens& artist : sorted_artists_plays) {
    top_artists_plays_file << rank << ": " << artist.artist << ": " << artist.plays.times_listened << endl;
    rank++;
  }
  
  // RANDOM STATS
  ofstream stats_file;
  stats_file.open(random_stats_path);
  long ms_total = 0;
  int plays = 0;
  for (const SongTotalListens& song : sorted_songs_ms) {
    ms_total += song.plays.milliseconds_listened;
    plays += song.plays.times_listened;
  }
  long ms = ms_total;
  //3600000 milliseconds in an hour
  long hr = ms / 3600000;
  ms = ms - 3600000 * hr;
  //60000 milliseconds in a minute
  long min = ms / 60000;
  ms = ms - 60000 * min;
  //1000 milliseconds in a second
  long sec = ms / 1000;
  ms = ms - 1000 * sec;
  
  stats_file << "You've listened to music for" << ": " << hr << " hr, "
            << min << " min, " << sec << " sec, " << ms << " ms" << endl;
  stats_file << "And played " << sorted_songs_ms.size() << " songs " << plays << " times" << endl;
  stats_file << "That's an average of " << plays / sorted_artists_ms.size() << " plays per song" << endl;
  // for an average of x minutes/plays / song
  
  // ARTISTS BREAKDOWN
  vector<vector<SongTotalListens> > songs_by_artist = GetSortedSongsByArtist(songs);
  ofstream artists_file;
  artists_file.open(artists_breakdown_path);
  int artist_rank = 1;
  for (int i = 0; i < songs_by_artist.size(); i++) {
    vector<SongTotalListens> song_listens = songs_by_artist[i];
    ArtistTotalListens artist = sorted_artists_ms[i];
    artists_file << "# " << artist_rank << ": " << artist << endl;
    artist_rank++;
    rank = 1;
    for (const SongTotalListens& song_listen : song_listens) {
      double percent_artist = (double) song_listen.plays.milliseconds_listened /
        (double) artist.plays.milliseconds_listened * 100;
      double percent_total = (double) song_listen.plays.milliseconds_listened / (double) ms_total * 100;
      artists_file << rank << ": " << song_listen << "\\" << endl;
      artists_file << "&nbsp; &nbsp; &nbsp;" << percent_artist
        << "% of the time you've spent listening to this artist" << "\\" << endl;
      artists_file << "&nbsp; &nbsp; &nbsp;" << percent_total
        << "% of the time you've spent listening to all your music" << "\\" << endl;
      rank++;
    }
    artists_file << endl;
  }
  
  // let's be real i will need this to debug again at some point
  /*ofstream songs_file;
  songs_file.open("MyData/songs.txt");
  i = 1;
  for (const SongListen& song : songs) {
    songs_file << i << ": " << song << endl;
    i++;
  }*/
  
  return EXIT_SUCCESS;
}
