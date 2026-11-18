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

    bool operator==(const AudioBuffer& other) const;
    bool operator!=(const AudioBuffer& other) const;
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

    size_t GetCapacity() const;
    size_t GetAvailableSamplesCount() const;
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