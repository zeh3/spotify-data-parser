cmake_minimum_required(VERSION 3.15)
project(spotify)

set(CMAKE_CXX_STANDARD 14)

add_executable(spotify apps/main.cpp)

# The library code is here.
add_subdirectory(src)

# The executable code is here.
add_subdirectory(apps)

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

#[[# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()]]

# JSON Library. Header-only.
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip
)


# Adds nlohmann_json library.
FetchContent_GetProperties(nlohmann_json)
if(NOT nlohmann_json_POPULATED)
    FetchContent_Populate(nlohmann_json)
    # add_library(nlohmann_json INTERFACE src/song_listens.cpp include/spotify/song_listens.h)
    # target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR}/single_include)
endif()
