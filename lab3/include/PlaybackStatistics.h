/**
 * @file PlaybackStatistics.h
 * @brief Declaration of the PlaybackStatistics class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYBACKSTATISTICS_H
#define PLAYBACKSTATISTICS_H

#include <iostream>
#include <string>

/**
 * @brief Aggregates playback telemetry, total listening hours, skip rates and favorite genre distributions.
 */
class PlaybackStatistics {
public:
    /**
     * @brief Constructs a PlaybackStatistics.
     * @param total_listen_time_sec Total seconds spent listening.
     * @param sessions_count Number of playback sessions started.
     * @param skips_count Number of skipped tracks.
     * @param favorite_genre Dominant genre listened.
     */
    PlaybackStatistics(double total_listen_time_sec = 0.0, int sessions_count = 0, int skips_count = 0, const std::string& favorite_genre = "Unknown");

    /**
     * @brief Compares two PlaybackStatistics instances for equality.
     * @param other Statistics to compare with.
     * @return true if metrics match.
     */
    bool operator==(const PlaybackStatistics& other) const;

    /**
     * @brief Compares two PlaybackStatistics instances for inequality.
     * @param other Statistics to compare with.
     * @return true if metrics differ.
     */
    bool operator!=(const PlaybackStatistics& other) const;

    /**
     * @brief Stream output operator for formatting PlaybackStatistics info.
     * @param os Output stream.
     * @param stats Statistics instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PlaybackStatistics& stats);

    /**
     * @brief Records a completed or partial song listening session.
     * @param listen_duration_sec Seconds listened in this session.
     * @param genre Genre of the track.
     * @param skipped Whether track was skipped before finishing.
     */
    void RecordSession(double listen_duration_sec, const std::string& genre, bool skipped = false);

    /**
     * @brief Calculates average session length in minutes.
     * @return Average session duration.
     */
    double GetAverageSessionMinutes() const;

    /**
     * @brief Computes skip rate percentage (0.0 to 100.0%).
     * @return Skip percentage.
     */
    double CalculateSkipRatePercentage() const;

    /**
     * @brief Resets all counters and statistics to zero.
     */
    void Reset();

    /**
     * @brief Gets cumulative listening duration in seconds.
     * @return Total seconds.
     */
    double GetTotalListenTimeSec() const;

    /**
     * @brief Gets total number of sessions logged.
     * @return Sessions count.
     */
    int GetSessionsCount() const;

    /**
     * @brief Gets total skipped tracks count.
     * @return Skips count.
     */
    int GetSkipsCount() const;

    /**
     * @brief Gets primary favorite genre.
     * @return Reference to genre string.
     */
    const std::string& GetFavoriteGenre() const;

private:
    double total_listen_time_sec_;
    int sessions_count_;
    int skips_count_;
    std::string favorite_genre_;
};

#endif