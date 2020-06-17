#### 5/20/2020
   - created project and (hopefully) linked json parsing library
    
#### 5/22/2020
   - added project to github
   - more linking -_-
   - i just feel the need to apologize for having the audacity to think this project was important enough or I was focused enough for a DEVELOPMENT.md; again I'm really sorry
    
#### 5/23/2020
   - finish main.cpp
   - finish example json for testing
   - laying groundwork for SortSongsByTime which intimidates me
    
#### 5/25/2020
   - basic test cases so I know it's not completely broken
   - more groundwork
    
#### 5/27/2020
   - finished SortSongsByTime
   - performance improvements
   - sorts artists
    
#### 5/28/2020
   - sorting by # of plays
   - refactoring
   - I fixed this one weird bug where songs with the same name weren't showing up in the songs lists, it turns out it was because of the way I overloaded the < operator- I made it so that was only dependent on the song name, which apparently meant the map treated each song with the same name as the same key. Fixed by making the < operator compare the concatonated song name and artist name.
   - breakdown sorted by artist, todo: add more data to that (%, etc)
   
#### 5/30/2020
   - added some stats to stats.txt

#### 6/8/2020
   - some cleanup and general improvements
   
#### 6/17/2020
   - one of my friends managed to do integer overflow. I congratulated him on the sheer amount of music he listens to and then made some changes so that everything deals with seconds instead of milliseconds. I don't think it's even possible to listen to enough music in a year to break it now?