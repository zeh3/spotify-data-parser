cmake_minimum_required(VERSION 3.15)
project(spotify)

set(CMAKE_CXX_STANDARD 14)

# The library code is here.
add_subdirectory(src)

# The executable code is here.
add_subdirectory(apps)

add_subdirectory(tests)

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

install(TARGETS main DESTINATION bin)


# Testing library. Header-only.
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.11.1
)

# JSON Library. Header-only.
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip
)


# Adds nlohmann_json library.
FetchContent_GetProperties(nlohmann_json)
if(NOT nlohmann_json_POPULATED)
    FetchContent_Populate(nlohmann_json)
    add_library(nlohmann_json INTERFACE)
    target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR}/single_include)
endif()

# Adds catch2 library.
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    # This is overkill since we only need a single file. Though it is a clean solution.
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()
