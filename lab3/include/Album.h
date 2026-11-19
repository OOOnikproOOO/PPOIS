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

    /**
     * @brief Compares two Album instances for equality.
     * @param other Album to compare with.
     * @return true if properties and tracklists match.
     */
    bool operator==(const Album& other) const;

    /**
     * @brief Compares two Album instances for inequality.
     * @param other Album to compare with.
     * @return true if properties or tracklists differ.
     */
    bool operator!=(const Album& other) const;

    /**
     * @brief Stream output operator for formatting Album info.
     * @param os Output stream.
     * @param album Album instance to display.
     * @return Reference to the output stream.
     */
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

    /**
     * @brief Gets album title.
     * @return Reference to title string.
     */
    const std::string& GetTitle() const;

    /**
     * @brief Gets release year.
     * @return Release year integer.
     */
    int GetReleaseYear() const;

    /**
     * @brief Gets record label name.
     * @return Reference to record label string.
     */
    const std::string& GetRecordLabel() const;

    /**
     * @brief Gets constant reference to tracklist vector.
     * @return Reference to vector of AudioTrack.
     */
    const std::vector<AudioTrack>& GetTracks() const;

    /**
     * @brief Gets count of tracks in the album.
     * @return Track count.
     */
    size_t GetTracksCount() const;

private:
    std::string title_;
    int release_year_;
    std::string record_label_;
    std::vector<AudioTrack> tracks_;
};

#endif