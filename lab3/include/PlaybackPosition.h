/**
 * @file PlaybackPosition.h
 * @brief Declaration of the PlaybackPosition class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYBACKPOSITION_H
#define PLAYBACKPOSITION_H

#include <iostream>
#include <string>

/**
 * @brief Tracks playback timestamp progression, seek actions and calculates timeline percentages.
 */
class PlaybackPosition {
public:
    /**
     * @brief Constructs a PlaybackPosition.
     * @param total_sec Total track length in seconds.
     * @param current_sec Initial position.
     * @param playback_speed Speed factor (e.g. 1.0x, 1.25x).
     */
    PlaybackPosition(double total_sec = 200.0, double current_sec = 0.0, double playback_speed = 1.0);

    /**
     * @brief Compares two PlaybackPosition instances for equality.
     * @param other Position to compare with.
     * @return true if timeline offsets match.
     */
    bool operator==(const PlaybackPosition& other) const;

    /**
     * @brief Compares two PlaybackPosition instances for inequality.
     * @param other Position to compare with.
     * @return true if timeline offsets differ.
     */
    bool operator!=(const PlaybackPosition& other) const;

    /**
     * @brief Stream output operator for formatting PlaybackPosition info.
     * @param os Output stream.
     * @param pos Position instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PlaybackPosition& pos);

    /**
     * @brief Steps playback time forward by delta factoring playback speed.
     * @param delta_sec Real wall clock seconds passed.
     */
    void Advance(double delta_sec);

    /**
     * @brief Jumps position directly to target second.
     * @param target_sec Desired timestamp.
     */
    void SeekTo(double target_sec);

    /**
     * @brief Computes playback progress percentage (0.0 to 100.0%).
     * @return Percentage completed.
     */
    double CalculateProgressPercent() const;

    /**
     * @brief Formats current time as 'MM:SS / MM:SS'.
     * @return Formatted progress string.
     */
    std::string FormatTimeElapsed() const;

    /**
     * @brief Resets current position back to zero.
     */
    void Reset();

    /**
     * @brief Gets current playback position in seconds.
     * @return Elapsed seconds.
     */
    double GetCurrentSec() const;

    /**
     * @brief Gets total track duration in seconds.
     * @return Total seconds.
     */
    double GetTotalSec() const;

    /**
     * @brief Gets active playback speed multiplier.
     * @return Speed factor.
     */
    double GetPlaybackSpeed() const;

    /**
     * @brief Checks if playback has reached the end of the track.
     * @return true if current position equals or exceeds total duration.
     */
    bool IsAtEnd() const;

private:
    double current_sec_;
    double total_sec_;
    bool is_seeking_;
    double playback_speed_;
};

#endif