/**
 * @file AudioEngine.h
 * @brief Declaration of the AudioEngine class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <iostream>
#include <string>
#include "AudioBuffer.h"

/**
 * @brief Low-level audio hardware playback engine managing states (Playing/Paused/Stopped) and sample delivery.
 */
class AudioEngine {
public:
    /**
     * @brief Constructs an AudioEngine.
     * @param sample_rate_hz Engine clock frequency in Hz.
     * @param buffer_capacity AudioBuffer FIFO size.
     */
    AudioEngine(int sample_rate_hz = 44100, size_t buffer_capacity = 2048);

    /**
     * @brief Compares two AudioEngine instances for equality.
     * @param other Engine to compare with.
     * @return true if state and sample rate match.
     */
    bool operator==(const AudioEngine& other) const;

    /**
     * @brief Compares two AudioEngine instances for inequality.
     * @param other Engine to compare with.
     * @return true if parameters differ.
     */
    bool operator!=(const AudioEngine& other) const;

    /**
     * @brief Stream output operator for formatting AudioEngine info.
     * @param os Output stream.
     * @param engine Engine instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioEngine& engine);

    /**
     * @brief Starts sound engine playback.
     */
    void Play();

    /**
     * @brief Pauses playback retaining buffer position.
     */
    void Pause();

    /**
     * @brief Stops playback and clears audio buffers.
     */
    void Stop();

    /**
     * @brief Renders audio samples from buffer to simulated DAC output.
     * @param samples_to_render Sample count to process.
     * @return Number of samples actually read and rendered.
     */
    size_t RenderAudioBuffer(size_t samples_to_render);

    /**
     * @brief Resets audio engine state and counters.
     */
    void ResetEngine();

    /**
     * @brief Gets current engine state ("Stopped", "Playing", "Paused").
     * @return Reference to state string.
     */
    const std::string& GetState() const;

    /**
     * @brief Gets hardware sample rate in Hz.
     * @return Sample rate in Hertz.
     */
    int GetSampleRateHz() const;

    /**
     * @brief Gets total buffer underrun occurrences.
     * @return Underrun events count.
     */
    int GetBufferUnderrunsCount() const;

    /**
     * @brief Gets mutable reference to internal playback AudioBuffer.
     * @return Reference to AudioBuffer.
     */
    AudioBuffer& GetBuffer();

    /**
     * @brief Gets constant reference to internal playback AudioBuffer.
     * @return Const reference to AudioBuffer.
     */
    const AudioBuffer& GetBuffer() const;

private:
    std::string state_;
    int sample_rate_hz_;
    int buffer_underruns_count_;
    AudioBuffer playback_buffer_;
};

#endif