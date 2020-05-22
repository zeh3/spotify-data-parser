# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS
        "spotify-data-parser/include/spotify/*.h"
        "spotify-data-parser/include/spotify/*.hpp")

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "spotify-data-parser/src/*.h"
        "spotify-data-parser/src/*.hpp"
        "spotify-data-parser/src/*.cc"
        "spotify-data-parser/src/*.cpp")

add_library(spotify song_listens.cpp)

target_include_directories(spotify PUBLIC ../include)