#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "playlist_period.h"
#include <vector>
#include <cstdint>

Playlist make_playlist(const std::vector<uint32_t> &durations) {
    std::vector<Song> songs;
    songs.reserve(durations.size());
    for (auto d: durations)
        songs.emplace_back(d);
    return Playlist(std::move(songs));
}

TEST_CASE("playlist_period - empty playlist") {
    auto playlist = make_playlist({});
    CHECK(playlist_period(playlist) == 0);
}

TEST_CASE("playlist_period - single song") {
    auto playlist = make_playlist({120});
    CHECK(playlist_period(playlist) == 120);
}

TEST_CASE("playlist_period - two songs") {
    auto playlist = make_playlist({120, 180});
    CHECK(playlist_period(playlist) == 300);
}

TEST_CASE("playlist_period - multiple songs") {
    auto playlist = make_playlist({60, 120, 180});
    CHECK(playlist_period(playlist) == 360);
}

TEST_CASE("playlist_period - all same durations") {
    auto playlist = make_playlist({42, 42, 42});
    CHECK(playlist_period(playlist) == 126);
}

TEST_CASE("playlist_period - varied durations") {
    auto playlist = make_playlist({10, 20, 30, 40, 50});
    CHECK(playlist_period(playlist) == 150);
}

TEST_CASE("playlist_period - large numbers") {
    auto playlist = make_playlist({1000, 2000, 3000});
    CHECK(playlist_period(playlist) == 6000);
}
