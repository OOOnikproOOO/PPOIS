/**
 * @file AudioStream.h
 * @brief Declaration of the AudioStream class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOSTREAM_H
#define AUDIOSTREAM_H

#include <iostream>
#include <string>
#include "AudioBuffer.h"

/**
 * @brief Manages linear streaming of audio samples with seeking and EOF detection.
 */
class AudioStream {
public:
    /**
     * @brief Constructs an AudioStream.
     * @param stream_source URL or local file path.
     * @param total_duration_sec Total stream length in seconds.
     * @param buffer_capacity Capacity of attached AudioBuffer.
     */
    AudioStream(const std::string& stream_source = "local://track.mp3", double total_duration_sec = 180.0, size_t buffer_capacity = 2048);

    /**
     * @brief Compares two AudioStream instances for equality.
     * @param other Stream to compare with.
     * @return true if properties match.
     */
    bool operator==(const AudioStream& other) const;

    /**
     * @brief Compares two AudioStream instances for inequality.
     * @param other Stream to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const AudioStream& other) const;

    /**
     * @brief Stream output operator for formatting AudioStream info.
     * @param os Output stream.
     * @param stream Stream instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioStream& stream);

    /**
     * @brief Simulates reading next chunk of audio into the stream buffer.
     * @param samples_count Number of samples to generate and push.
     * @return Number of samples pushed to buffer.
     */
    size_t ReadNextChunk(size_t samples_count);

    /**
     * @brief Seeks playback stream position to a given timestamp.
     * @param position_sec Target position in seconds.
     */
    void Seek(double position_sec);

    /**
     * @brief Rewinds stream back to start.
     */
    void ResetStream();

    /**
     * @brief Computes remaining playback duration.
     * @return Remaining seconds.
     */
    double GetRemainingTimeSec() const;

    /**
     * @brief Gets stream source path or URL.
     * @return Reference to stream source string.
     */
    const std::string& GetStreamSource() const;

    /**
     * @brief Gets total stream duration in seconds.
     * @return Duration in seconds.
     */
    double GetTotalDurationSec() const;

    /**
     * @brief Gets current stream read position in seconds.
     * @return Current seconds.
     */
    double GetCurrentPositionSec() const;

    /**
     * @brief Checks if stream reached end of file.
     * @return true if EOF reached.
     */
    bool IsEof() const;

    /**
     * @brief Gets constant reference to internal AudioBuffer.
     * @return Reference to AudioBuffer.
     */
    const AudioBuffer& GetBuffer() const;

private:
    std::string stream_source_;
    double total_duration_sec_;
    double current_position_sec_;
    bool is_eof_;
    AudioBuffer buffer_;
};

#endif