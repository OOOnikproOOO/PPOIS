/**
 * @file Album.h
 * @brief Declaration of the Album class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include <vector>
#include "AudioTrack.h"

/**
 * @brief Represents a musical album grouping tracks under a title and release year.
 */
class Album {
public:
    /**
     * @brief Constructs an Album.
     * @param title Album title.
     * @param release_year Year published.
     * @param record_label Publishing record label.
     */
    Album(const std::string& title = "Untitled Album", int release_year = 2026, const std::string& record_label = "Independent");

    bool operator==(const Album& other) const;
    bool operator!=(const Album& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Album& album);

    /**
     * @brief Appends an audio track to the album tracklist.
     * @param track AudioTrack to add.
     */
    void AddTrack(const AudioTrack& track);

    /**
     * @brief Removes a track by exact title match.
     * @param track_title Title of track to remove.
     * @throws TrackNotFoundException if track is not found.
     */
    void RemoveTrack(const std::string& track_title);

    /**
     * @brief Calculates total album playtime in seconds.
     * @return Sum of track durations.
     */
    double CalculateTotalDurationSec() const;

    /**
     * @brief Finds a track in the album by title.
     * @param track_title Title to search.
     * @return Pointer to found AudioTrack, or nullptr.
     */
    const AudioTrack* FindTrack(const std::string& track_title) const;

    const std::string& GetTitle() const;
    int GetReleaseYear() const;
    const std::string& GetRecordLabel() const;
    const std::vector<AudioTrack>& GetTracks() const;
    size_t GetTracksCount() const;

private:
    std::string title_;
    int release_year_;
    std::string record_label_;
    std::vector<AudioTrack> tracks_;
};

#endif