/**
 * @file Playlist.h
 * @brief Declaration of the Playlist class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
#include <vector>
#include "AudioTrack.h"

/**
 * @brief Represents a user-curated playlist with capacity constraints and track reordering.
 */
class Playlist {
public:
    /**
     * @brief Constructs a Playlist.
     * @param name Name of playlist.
     * @param is_public Visibility status.
     * @param max_capacity Maximum tracks allowed in playlist.
     */
    Playlist(const std::string& name = "My Playlist", bool is_public = true, size_t max_capacity = 1000);

    bool operator==(const Playlist& other) const;
    bool operator!=(const Playlist& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);

    /**
     * @brief Adds a track to the end of the playlist.
     * @param track Track to add.
     * @throws PlaylistFullException when max_capacity is reached.
     */
    void AddTrack(const AudioTrack& track);

    /**
     * @brief Removes a track at a given index.
     * @param index Zero-based index.
     * @throws TrackNotFoundException if index is out of bounds.
     */
    void RemoveTrack(size_t index);

    /**
     * @brief Moves a track from one index to another.
     * @param from_idx Source index.
     * @param to_idx Destination index.
     * @throws TrackNotFoundException if an index is out of bounds.
     */
    void MoveTrack(size_t from_idx, size_t to_idx);

    /**
     * @brief Computes total playtime of all tracks in playlist.
     * @return Duration in seconds.
     */
    double CalculateTotalDurationSec() const;

    /**
     * @brief Clears all tracks from the playlist.
     */
    void Clear();

    const std::string& GetName() const;
    bool IsPublic() const;
    size_t GetMaxCapacity() const;
    const std::vector<AudioTrack>& GetTracks() const;
    size_t GetTracksCount() const;

private:
    std::string name_;
    bool is_public_;
    size_t max_capacity_;
    std::vector<AudioTrack> tracks_;
};

#endif