#pragma once
#include <vector>
#include <cstdint>
#include <cassert>

class Song {
    std::uint32_t m_duration;

public:
    explicit Song(const std::uint32_t duration) : m_duration(duration) {
        assert(duration > 0);
    }

    [[nodiscard]] std::uint32_t duration() const noexcept { return m_duration; }
};

class Playlist {
    std::vector<Song> m_songs;

public:
    explicit Playlist(std::vector<Song> songs) : m_songs(std::move(songs)) {
    }

    [[nodiscard]] const Song &operator[](const std::size_t index) const noexcept {
        assert(index < size());
        return m_songs[index];
    }

    [[nodiscard]] std::size_t size() const noexcept { return m_songs.size(); }
};

[[nodiscard]] std::uint32_t playlist_period(const Playlist &playlist);
