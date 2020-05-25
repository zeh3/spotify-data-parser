//
// Created by Lou Zeh on 5/22/20.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "spotify/song_listens.h"

using std::string;
using std::ifstream;
using namespace spotify;

TEST_CASE("test parsing", "[ParseJson]") {
  string example_file_path = "data/ExampleOneDay.json";
  ifstream json_stream(example_file_path);
  json j;
  json_stream >> j;
  vector<json> json_vector = j.get<std::vector<json> >();
  vector<SongListen> song_listens = ParseJson(json_vector);
  
  Song bleh("bleh", "example artist");
  string first_time = "1995-02-19 1:15";
  long first_ms = 1000;
  SongListen first(bleh, first_ms, first_time);
  REQUIRE(first == song_listens[0]);
  
  Song sorry("I'm sorry", "me");
  string ninth_time = "1995-02-19 10:15";
  long ninth_ms = 200;
  SongListen ninth(sorry, ninth_ms, ninth_time);
  REQUIRE(ninth == song_listens[9]);
  
}



