/**
 * @file PlaybackHistory.h
 * @brief Declaration of the PlaybackHistory class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYBACKHISTORY_H
#define PLAYBACKHISTORY_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Logs history of recently played tracks with timestamps and query capabilities.
 */
class PlaybackHistory {
public:
    /**
     * @brief Constructs a PlaybackHistory.
     * @param max_entries Capacity limit of history log.
     */
    explicit PlaybackHistory(size_t max_entries = 100);

    /**
     * @brief Compares two PlaybackHistory instances for equality.
     * @param other History to compare with.
     * @return true if entries and counters match.
     */
    bool operator==(const PlaybackHistory& other) const;

    /**
     * @brief Compares two PlaybackHistory instances for inequality.
     * @param other History to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PlaybackHistory& other) const;

    /**
     * @brief Stream output operator for formatting PlaybackHistory info.
     * @param os Output stream.
     * @param history History instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PlaybackHistory& history);

    /**
     * @brief Records a played track into history.
     * @param track_title Track title or artist tag.
     */
    void RecordTrack(const std::string& track_title);

    /**
     * @brief Returns a sublist of the N most recently played songs.
     * @param count Number of recent entries requested.
     * @return Vector of track titles.
     */
    std::vector<std::string> GetRecentTracks(size_t count) const;

    /**
     * @brief Checks if a song was ever played in recorded history.
     * @param track_title Title to check.
     * @return true if found.
     */
    bool ContainsRecord(const std::string& track_title) const;

    /**
     * @brief Clears entire listening history.
     */
    void ClearHistory();

    /**
     * @brief Gets maximum entries capacity.
     * @return Capacity count.
     */
    size_t GetMaxEntries() const;

    /**
     * @brief Gets current count of recorded history entries.
     * @return Entries count.
     */
    size_t GetEntriesCount() const;

    /**
     * @brief Gets total all-time play count.
     * @return Total played count.
     */
    int GetTotalPlayedCount() const;

    /**
     * @brief Gets constant reference to history records vector.
     * @return Reference to vector of track title strings.
     */
    const std::vector<std::string>& GetRecords() const;

private:
    size_t max_entries_;
    std::vector<std::string> history_records_;
    int total_played_count_;
};

#endif