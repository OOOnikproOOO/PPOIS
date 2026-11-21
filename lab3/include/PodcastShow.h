/**
 * @file PodcastShow.h
 * @brief Declaration of the PodcastShow class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PODCASTSHOW_H
#define PODCASTSHOW_H

#include <iostream>
#include <string>
#include <vector>
#include "PodcastEpisode.h"

/**
 * @brief Represents a serialized podcast show series hosting an episode catalog.
 */
class PodcastShow {
public:
    /**
     * @brief Constructs a PodcastShow.
     * @param show_title Show commercial title.
     * @param host_name Author or podcaster host name.
     * @param category Thematic category.
     */
    PodcastShow(const std::string& show_title = "The Tech Frontier", const std::string& host_name = "OOOnikproOOO", const std::string& category = "Technology");

    /**
     * @brief Compares two PodcastShow instances for equality.
     * @param other Show to compare with.
     * @return true if title and host match.
     */
    bool operator==(const PodcastShow& other) const;

    /**
     * @brief Compares two PodcastShow instances for inequality.
     * @param other Show to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PodcastShow& other) const;

    /**
     * @brief Stream output operator for formatting PodcastShow info.
     * @param os Output stream.
     * @param show Show instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PodcastShow& show);

    /**
     * @brief Adds a new episode to the show catalog.
     * @param episode PodcastEpisode to append.
     */
    void AddEpisode(const PodcastEpisode& episode);

    /**
     * @brief Searches for an episode by number.
     * @param episode_number Sequence number to search.
     * @return Const reference to found PodcastEpisode.
     * @throws TrackNotFoundException if episode number does not exist.
     */
    const PodcastEpisode& FindEpisode(int episode_number) const;

    /**
     * @brief Counts number of episodes not yet marked as listened.
     * @return Unlistened episodes count.
     */
    size_t GetUnlistenedCount() const;

    /**
     * @brief Calculates total broadcast duration of all show episodes.
     * @return Cumulative duration in seconds.
     */
    double CalculateTotalDurationSec() const;

    /**
     * @brief Gets show title.
     * @return Reference to title string.
     */
    const std::string& GetShowTitle() const;

    /**
     * @brief Gets host name.
     * @return Reference to host name string.
     */
    const std::string& GetHostName() const;

    /**
     * @brief Gets thematic category.
     * @return Reference to category string.
     */
    const std::string& GetCategory() const;

    /**
     * @brief Gets constant reference to episode list.
     * @return Reference to vector of PodcastEpisode.
     */
    const std::vector<PodcastEpisode>& GetEpisodes() const;

private:
    std::string show_title_;
    std::string host_name_;
    std::string category_;
    std::vector<PodcastEpisode> episodes_;
};

#endif