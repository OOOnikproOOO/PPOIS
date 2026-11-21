/**
 * @file AudioMetadata.h
 * @brief Declaration of the AudioMetadata class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOMETADATA_H
#define AUDIOMETADATA_H

#include <iostream>
#include <string>

/**
 * @brief Stores descriptive metadata and ID3 tags for an audio track.
 */
class AudioMetadata {
public:
    /**
     * @brief Constructs AudioMetadata with track attributes.
     * @param title Track title.
     * @param artist Artist name.
     * @param album Album name.
     * @param genre Music genre.
     * @param year Release year.
     * @param track_number Track index in album.
     */
    AudioMetadata(const std::string& title = "Unknown Title", const std::string& artist = "Unknown Artist", const std::string& album = "Unknown Album", const std::string& genre = "Soundtrack", int year = 2026, int track_number = 1);

    /**
     * @brief Compares two AudioMetadata instances for equality.
     * @param other Metadata to compare with.
     * @return true if all tags match.
     */
    bool operator==(const AudioMetadata& other) const;

    /**
     * @brief Compares two AudioMetadata instances for inequality.
     * @param other Metadata to compare with.
     * @return true if tags differ.
     */
    bool operator!=(const AudioMetadata& other) const;

    /**
     * @brief Stream output operator for formatting AudioMetadata info.
     * @param os Output stream.
     * @param meta Metadata instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioMetadata& meta);

    /**
     * @brief Updates all metadata tags simultaneously.
     * @param title Track title.
     * @param artist Artist name.
     * @param album Album name.
     * @param genre Music genre.
     * @param year Release year.
     * @param track_number Track index in album.
     */
    void UpdateMetadata(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre, int year, int track_number);

    /**
     * @brief Formats track info as 'Artist - Title (Year)'.
     * @return Formatted string representation.
     */
    std::string FormatDisplayString() const;

    /**
     * @brief Checks if metadata matches search query substring in title or artist.
     * @param query Search query.
     * @return true if match found.
     */
    bool MatchesQuery(const std::string& query) const;

    /**
     * @brief Validates metadata fields for logical correctness.
     * @return true if year and track number are within valid ranges.
     */
    bool Validate() const;

    /**
     * @brief Gets track title.
     * @return Reference to title string.
     */
    const std::string& GetTitle() const;

    /**
     * @brief Gets artist name.
     * @return Reference to artist string.
     */
    const std::string& GetArtist() const;

    /**
     * @brief Gets album name.
     * @return Reference to album string.
     */
    const std::string& GetAlbum() const;

    /**
     * @brief Gets musical genre.
     * @return Reference to genre string.
     */
    const std::string& GetGenre() const;

    /**
     * @brief Gets release year.
     * @return Year integer.
     */
    int GetYear() const;

    /**
     * @brief Gets track sequence number in album.
     * @return Track number integer.
     */
    int GetTrackNumber() const;

private:
    std::string title_;
    std::string artist_;
    std::string album_;
    std::string genre_;
    int year_;
    int track_number_;
};

#endif