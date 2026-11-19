/**
 * @file AudioBuffer.h
 * @brief Declaration of the AudioBuffer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <iostream>
#include <vector>
#include "AudioSample.h"

/**
 * @brief Circular FIFO buffer storing PCM audio samples for glitch-free playback.
 */
class AudioBuffer {
public:
    /**
     * @brief Constructs an AudioBuffer with a specified sample capacity.
     * @param capacity_samples Maximum samples held simultaneously.
     */
    explicit AudioBuffer(size_t capacity_samples = 4096);

    /**
     * @brief Compares two AudioBuffer instances for equality.
     * @param other Buffer to compare with.
     * @return true if properties match.
     */
    bool operator==(const AudioBuffer& other) const;

    /**
     * @brief Compares two AudioBuffer instances for inequality.
     * @param other Buffer to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const AudioBuffer& other) const;

    /**
     * @brief Stream output operator for formatting AudioBuffer info.
     * @param os Output stream.
     * @param buffer Buffer instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioBuffer& buffer);

    /**
     * @brief Pushes an audio sample into the buffer.
     * @param sample Audio sample to store.
     * @return true if sample was successfully written.
     */
    bool WriteSample(const AudioSample& sample);

    /**
     * @brief Pulls the next audio sample from the buffer.
     * @return Extracted AudioSample.
     * @throws PlaybackBufferUnderflowException when reading from an empty buffer.
     */
    AudioSample ReadSample();

    /**
     * @brief Resets read/write pointers and empties the buffer.
     */
    void Clear();

    /**
     * @brief Returns current buffer fullness percentage (0.0 to 100.0%).
     * @return Percentage filled.
     */
    double GetOccupancyPercentage() const;

    /**
     * @brief Gets maximum sample storage capacity.
     * @return Capacity in samples.
     */
    size_t GetCapacity() const;

    /**
     * @brief Gets current number of available readable samples.
     * @return Sample count.
     */
    size_t GetAvailableSamplesCount() const;

    /**
     * @brief Checks if buffer experienced an underrun condition.
     * @return true if underrun occurred.
     */
    bool IsUnderrun() const;

private:
    std::vector<AudioSample> samples_;
    size_t capacity_samples_;
    size_t read_index_;
    size_t write_index_;
    size_t count_;
    bool is_underrun_;
};

#endif