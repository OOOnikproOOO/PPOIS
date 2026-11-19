/**
 * @file Bookmark.h
 * @brief Declaration of the Bookmark class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <iostream>
#include <string>

/**
 * @brief Represents a user timestamp bookmark with annotations in long audio tracks or podcasts.
 */
class Bookmark {
public:
    /**
     * @brief Constructs a Bookmark.
     * @param track_title Target track title.
     * @param timestamp_sec Position in seconds.
     * @param note User description or chapter label.
     * @param creation_date Date tag string.
     */
    Bookmark(const std::string& track_title = "Untitled", double timestamp_sec = 0.0, const std::string& note = "Bookmark Note", const std::string& creation_date = "2026.11.19");

    /**
     * @brief Compares two Bookmark instances for equality.
     * @param other Bookmark to compare with.
     * @return true if properties match.
     */
    bool operator==(const Bookmark& other) const;

    /**
     * @brief Compares two Bookmark instances for inequality.
     * @param other Bookmark to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const Bookmark& other) const;

    /**
     * @brief Stream output operator for formatting Bookmark info.
     * @param os Output stream.
     * @param bm Bookmark instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Bookmark& bm);

    /**
     * @brief Formats bookmark as 'Title @ MM:SS (Note)'.
     * @return Formatted string.
     */
    std::string FormatBookmarkString() const;

    /**
     * @brief Updates user note text.
     * @param new_note New annotation.
     */
    void UpdateNote(const std::string& new_note);

    /**
     * @brief Shifts bookmark timestamp by delta.
     * @param delta_sec Seconds offset.
     */
    void AdjustTimestamp(double delta_sec);

    /**
     * @brief Gets associated track title.
     * @return Reference to track title string.
     */
    const std::string& GetTrackTitle() const;

    /**
     * @brief Gets bookmark timestamp in seconds.
     * @return Seconds offset.
     */
    double GetTimestampSec() const;

    /**
     * @brief Gets bookmark annotation note.
     * @return Reference to note string.
     */
    const std::string& GetNote() const;

    /**
     * @brief Gets creation date string.
     * @return Reference to creation date string.
     */
    const std::string& GetCreationDate() const;

private:
    std::string track_title_;
    double timestamp_sec_;
    std::string note_;
    std::string creation_date_;
};

#endif