/**
 * @file ID3TagEditor.h
 * @brief Declaration of the ID3TagEditor class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef ID3TAGEDITOR_H
#define ID3TAGEDITOR_H

#include <iostream>
#include <string>
#include "AudioTrack.h"

/**
 * @brief Provides metadata inspection, batch tag editing and UTF-8 ID3 frame modification for tracks.
 */
class ID3TagEditor {
public:
    /**
     * @brief Constructs an ID3TagEditor.
     * @param tag_version ID3 specification version (e.g. 2 for ID3v2.4).
     * @param encoding Text character encoding string ("UTF-8", "ISO-8859-1").
     * @param default_comment User tag commentary.
     */
    ID3TagEditor(int tag_version = 2, const std::string& encoding = "UTF-8", const std::string& default_comment = "");

    /**
     * @brief Compares two ID3TagEditor instances for equality.
     * @param other Editor to compare with.
     * @return true if properties match.
     */
    bool operator==(const ID3TagEditor& other) const;

    /**
     * @brief Compares two ID3TagEditor instances for inequality.
     * @param other Editor to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const ID3TagEditor& other) const;

    /**
     * @brief Stream output operator for formatting ID3TagEditor info.
     * @param os Output stream.
     * @param editor Editor instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ID3TagEditor& editor);

    /**
     * @brief Updates AudioTrack metadata tags and marks editor state as modified.
     * @param track Target track to modify.
     * @param title Track title.
     * @param artist Artist name.
     * @param album Album name.
     * @param genre Music genre.
     * @param year Release year.
     * @param track_number Track index number.
     */
    void ApplyTags(AudioTrack& track, const std::string& title, const std::string& artist, const std::string& album, const std::string& genre, int year, int track_number);

    /**
     * @brief Appends comment annotation to the tag.
     * @param comment Commentary text.
     */
    void SetComment(const std::string& comment);

    /**
     * @brief Commits tag changes and resets dirty status flag.
     */
    void SaveChanges();

    /**
     * @brief Discards pending tag changes.
     */
    void RevertChanges();

    /**
     * @brief Gets ID3 tag major version.
     * @return Version integer.
     */
    int GetTagVersion() const;

    /**
     * @brief Gets character encoding format string.
     * @return Reference to encoding string.
     */
    const std::string& GetEncoding() const;

    /**
     * @brief Gets attached commentary string.
     * @return Reference to comment string.
     */
    const std::string& GetComment() const;

    /**
     * @brief Checks if tags have unsaved modifications.
     * @return true if modified.
     */
    bool IsDirty() const;

private:
    int tag_version_;
    std::string encoding_;
    std::string comment_;
    bool is_dirty_;
};

#endif