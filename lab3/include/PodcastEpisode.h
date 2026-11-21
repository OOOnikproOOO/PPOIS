/**
 * @file PodcastEpisode.h
 * @brief Declaration of the PodcastEpisode class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PODCASTEPISODE_H
#define PODCASTEPISODE_H

#include <iostream>
#include <string>

/**
 * @brief Represents an individual podcast broadcast release with episode index, duration and listened state.
 */
class PodcastEpisode {
public:
    /**
     * @brief Constructs a PodcastEpisode.
     * @param title Episode title.
     * @param episode_number Episode sequence index.
     * @param duration_sec Runtime duration in seconds.
     * @param release_date Publication date string (YYYY.MM.DD).
     * @param is_listened Listened completion flag.
     */
    PodcastEpisode(const std::string& title = "Episode 1", int episode_number = 1, double duration_sec = 3600.0, const std::string& release_date = "2026.01.01", bool is_listened = false);

    /**
     * @brief Compares two PodcastEpisode instances for equality.
     * @param other Episode to compare with.
     * @return true if episode number and title match.
     */
    bool operator==(const PodcastEpisode& other) const;

    /**
     * @brief Compares two PodcastEpisode instances for inequality.
     * @param other Episode to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PodcastEpisode& other) const;

    /**
     * @brief Stream output operator for formatting PodcastEpisode info.
     * @param os Output stream.
     * @param ep Episode instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PodcastEpisode& ep);

    /**
     * @brief Marks episode as listened or unlistened.
     * @param listened State flag.
     */
    void MarkAsListened(bool listened = true);

    /**
     * @brief Formats episode summary as '#Number: Title (Duration min) [Status]'.
     * @return Formatted summary string.
     */
    std::string FormatEpisodeSummary() const;

    /**
     * @brief Updates episode runtime duration.
     * @param sec Seconds.
     */
    void UpdateDuration(double sec);

    /**
     * @brief Gets episode title.
     * @return Reference to title string.
     */
    const std::string& GetTitle() const;

    /**
     * @brief Gets episode sequence index number.
     * @return Episode number integer.
     */
    int GetEpisodeNumber() const;

    /**
     * @brief Gets duration in seconds.
     * @return Seconds.
     */
    double GetDurationSec() const;

    /**
     * @brief Gets release date string.
     * @return Reference to date string.
     */
    const std::string& GetReleaseDate() const;

    /**
     * @brief Checks if episode was marked as listened.
     * @return true if listened.
     */
    bool IsListened() const;

private:
    std::string title_;
    int episode_number_;
    double duration_sec_;
    std::string release_date_;
    bool is_listened_;
};

#endif