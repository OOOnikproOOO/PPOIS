/**
 * @file LyricLine.h
 * @brief Declaration of the LyricLine class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef LYRICLINE_H
#define LYRICLINE_H

#include <iostream>
#include <string>

/**
 * @brief Represents a single synchronized lyrics line with a timestamp and chorus marker.
 */
class LyricLine {
public:
    /**
     * @brief Constructs a LyricLine.
     * @param timestamp_sec Line activation time in seconds.
     * @param text Lyrical text content.
     * @param is_chorus Whether this line is part of a refrain or chorus.
     */
    LyricLine(double timestamp_sec = 0.0, const std::string& text = "", bool is_chorus = false);

    /**
     * @brief Compares two LyricLine instances for equality.
     * @param other Line to compare with.
     * @return true if timestamp and text match.
     */
    bool operator==(const LyricLine& other) const;

    /**
     * @brief Compares two LyricLine instances for inequality.
     * @param other Line to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const LyricLine& other) const;

    /**
     * @brief Stream output operator for formatting LyricLine info.
     * @param os Output stream.
     * @param line LyricLine instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const LyricLine& line);

    /**
     * @brief Formats line with timestamp as '[MM:SS.xx] Text'.
     * @return Formatted string representation.
     */
    std::string FormatTimestampedLine() const;

    /**
     * @brief Checks if this line is active at given playback position.
     * @param current_time Current playback time in seconds.
     * @param display_duration_sec Window duration in seconds line remains on screen.
     * @return true if active.
     */
    bool IsActiveAt(double current_time, double display_duration_sec = 4.0) const;

    /**
     * @brief Sets lyric text content.
     * @param text New lyrics line text.
     */
    void SetText(const std::string& text);

    /**
     * @brief Shifts line timestamp by delta seconds.
     * @param delta_sec Offset in seconds.
     */
    void AdjustTimestamp(double delta_sec);

    /**
     * @brief Gets line timestamp in seconds.
     * @return Seconds offset.
     */
    double GetTimestampSec() const;

    /**
     * @brief Gets lyrics text content.
     * @return Reference to text string.
     */
    const std::string& GetText() const;

    /**
     * @brief Checks if line is part of a chorus.
     * @return true if chorus.
     */
    bool IsChorus() const;

private:
    double timestamp_sec_;
    std::string text_;
    bool is_chorus_;
};

#endif