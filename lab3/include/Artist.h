/**
 * @file Artist.h
 * @brief Declaration of the Artist class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef ARTIST_H
#define ARTIST_H

#include <iostream>
#include <string>
#include <vector>
#include "Album.h"

/**
 * @brief Represents a musical artist or band with a discography of albums.
 */
class Artist {
public:
    /**
     * @brief Constructs an Artist profile.
     * @param name Artist name.
     * @param country Origin country.
     * @param monthly_listeners Monthly streaming listener count.
     */
    Artist(const std::string& name = "Unknown Artist", const std::string& country = "Unknown", int monthly_listeners = 0);

    /**
     * @brief Compares two Artist instances for equality.
     * @param other Artist to compare with.
     * @return true if properties and albums match.
     */
    bool operator==(const Artist& other) const;

    /**
     * @brief Compares two Artist instances for inequality.
     * @param other Artist to compare with.
     * @return true if properties or albums differ.
     */
    bool operator!=(const Artist& other) const;

    /**
     * @brief Stream output operator for formatting Artist info.
     * @param os Output stream.
     * @param artist Artist instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);

    /**
     * @brief Adds an album to the artist discography.
     * @param album Album to add.
     */
    void AddAlbum(const Album& album);

    /**
     * @brief Computes total songs released across all albums.
     * @return Track count.
     */
    size_t CalculateTotalTracksCount() const;

    /**
     * @brief Searches for an album by title.
     * @param album_title Title to find.
     * @return Pointer to Album or nullptr.
     */
    const Album* FindAlbum(const std::string& album_title) const;

    /**
     * @brief Updates monthly listeners counter.
     * @param delta Change in listener count.
     */
    void UpdateMonthlyListeners(int delta);

    /**
     * @brief Gets artist name.
     * @return Reference to name string.
     */
    const std::string& GetName() const;

    /**
     * @brief Gets artist country of origin.
     * @return Reference to country string.
     */
    const std::string& GetCountry() const;

    /**
     * @brief Gets count of monthly listeners.
     * @return Number of listeners.
     */
    int GetMonthlyListeners() const;

    /**
     * @brief Gets discography albums list.
     * @return Reference to vector of Album instances.
     */
    const std::vector<Album>& GetAlbums() const;

private:
    std::string name_;
    std::string country_;
    int monthly_listeners_;
    std::vector<Album> albums_;
};

#endif