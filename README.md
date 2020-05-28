# Spotify Data Parser
Parses downloaded spotify data to produce a few interesting lists. Like spotify wrapped but less pretty and with more data

## If you would like to use it
- clone the repo
- download and unzip your spotify data (it'll take a few days for spotify to send you your data) into a folder that should be called "MyData" 
- move that folder into the top level directory of your project
- My spotify data had 4 StreamingHistory.json files- yours might have a different number, so adjust the file_paths vector in main.cpp as necessary
- compile and run the program (it might take a while- I'm working on that)
- your stats should appear in TopSongsMs.txt in your MyData folder
- feel free to shoot me an email or make an issue if you run into any problems



## current features:
- ranking songs by the amount of time you've spent listening to them

## features to come:
- songs ranked
- longest listening sessions
- longest listening sessions but like over the whole day? (maybe)
- artists ranked
- songs ranked by times you listened instead of total time (min # of milliseconds to count as listen)
- number of times you skipped a song/only listened to first x seconds
