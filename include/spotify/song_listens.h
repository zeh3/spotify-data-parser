//
// Created by Lou Zeh on 5/20/20.
//

#ifndef SPOTIFY_SONG_LISTENS_H
#define SPOTIFY_SONG_LISTENS_H

#include <string>

using std::string;

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

}



#endif //SPOTIFY_SONG_LISTENS_H
