# Spotify Data Parser
Parses downloaded spotify data to produce a few interesting lists. Like spotify wrapped but less pretty and with more data

## If you would like to use it
- clone the repo
- download and unzip your spotify data (it'll take a few days for spotify to send you your data) into a folder that should be called "MyData" 
- move that folder into the top level directory of your project
- My spotify data had 4 StreamingHistory.json files- yours might have a different number, so adjust the file_paths vector in main.cpp as necessary
- compile and run the program
- your stats should appear in these files in your MyData file: TopSongsTime.txt, TopSongsPlays.txt, TopArtistsTime.txt, TopArtistsPlays.txt, stats.txt
- feel free to shoot me an email or make an issue if you run into any problems

## current features:
- ranking songs & artists by the amount of time you've spent listening to them
- ranking songs & artists by the number of times you've played them/their songs
- songs broken down and ranked by artist

## features to come:
- longest listening sessions
- longest listening sessions but like over the whole day? (maybe, full disclosure, that sounds hard)
- min # of milliseconds to count as a listen?
- number of times you skipped a song/only listened to first x seconds
- total time listening to music
- % of time listening to x song
- see how similar lists by ms and lists by plays are (?)
- breakdown of time spent listening to each song by % for each artist
- how many songs you've heard from each artist
