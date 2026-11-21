/**
 * @file SmartPlaylist.h
 * @brief Declaration of the SmartPlaylist class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SMARTPLAYLIST_H
#define SMARTPLAYLIST_H

#include <iostream>
#include <string>
#include <vector>
#include "Playlist.h"

/**
 * @brief Automatically populates tracks by filtering a library according to criteria.
 */
class SmartPlaylist {
public:
    /**
     * @brief Constructs a SmartPlaylist.
     * @param playlist_name Playlist name.
     * @param genre_filter Target genre filter.
     * @param min_year Minimum release year.
     * @param favorites_only Whether to only match favorite tracks.
     */
    SmartPlaylist(const std::string& playlist_name = "Smart Rock Mix", const std::string& genre_filter = "Rock", int min_year = 2000, bool favorites_only = false);

    /**
     * @brief Compares two SmartPlaylist instances for equality.
     * @param other Playlist to compare with.
     * @return true if filter criteria and playlists match.
     */
    bool operator==(const SmartPlaylist& other) const;

    /**
     * @brief Compares two SmartPlaylist instances for inequality.
     * @param other Playlist to compare with.
     * @return true if filter criteria or playlists differ.
     */
    bool operator!=(const SmartPlaylist& other) const;

    /**
     * @brief Stream output operator for formatting SmartPlaylist info.
     * @param os Output stream.
     * @param sp SmartPlaylist instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SmartPlaylist& sp);

    /**
     * @brief Evaluates an audio track against filter rules.
     * @param track AudioTrack to test.
     * @return true if track matches all criteria.
     */
    bool MatchesCriteria(const AudioTrack& track) const;

    /**
     * @brief Populates internal playlist from a candidate list of library tracks.
     * @param library_tracks Vector of available tracks.
     * @return Number of matching tracks added.
     */
    size_t ApplyFilter(const std::vector<AudioTrack>& library_tracks);

    /**
     * @brief Updates genre filter.
     * @param genre New genre string.
     */
    void SetGenreFilter(const std::string& genre);

    /**
     * @brief Updates minimum release year threshold.
     * @param year Minimum year.
     */
    void SetMinYear(int year);

    /**
     * @brief Toggles favorite-only filter mode.
     * @param enable Status flag.
     */
    void SetFavoritesOnly(bool enable);

    /**
     * @brief Gets current genre filter rule.
     * @return Reference to genre string.
     */
    const std::string& GetGenreFilter() const;

    /**
     * @brief Gets minimum release year filter threshold.
     * @return Minimum year.
     */
    int GetMinYear() const;

    /**
     * @brief Checks if filter selects favorites only.
     * @return true if favorites only.
     */
    bool IsFavoritesOnly() const;

    /**
     * @brief Gets reference to underlying populated Playlist.
     * @return Reference to Playlist.
     */
    const Playlist& GetPlaylist() const;

private:
    std::string genre_filter_;
    int min_year_;
    bool favorites_only_;
    Playlist playlist_;
};

#endif