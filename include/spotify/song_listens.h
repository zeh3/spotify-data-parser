//
// Created by Lou Zeh on 5/20/20.
//

#ifndef SPOTIFY_SONG_LISTENS_H
#define SPOTIFY_SONG_LISTENS_H

using std::string;

namespace spotify {

struct Song {
  string name;
  string artist;
};

class SongListens {
public:
  Song song;
  long milliseconds_listened;
};

}



#endif //SPOTIFY_SONG_LISTENS_H
