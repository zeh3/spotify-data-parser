# This target runs all of the tests.
# Make sure CATCH_CONFIG_MAIN is only defined in one test file.
add_executable(test-spotify test_spotify.cpp)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(test-spotify PRIVATE spotify catch2)

target_include_directories(spotify PUBLIC ../include)
