/**
 * @file AudioRecorder.h
 * @brief Declaration of the AudioRecorder class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <iostream>
#include "AudioBuffer.h"

/**
 * @brief Captures live microphone input into an AudioBuffer with duration and state tracking.
 */
class AudioRecorder {
public:
    /**
     * @brief Constructs an AudioRecorder.
     * @param sample_rate_hz Hardware capture sample rate in Hz.
     * @param buffer_capacity AudioBuffer FIFO size in samples.
     * @param is_recording Recording active toggle.
     */
    AudioRecorder(int sample_rate_hz = 44100, size_t buffer_capacity = 4096, bool is_recording = false);

    /**
     * @brief Compares two AudioRecorder instances for equality.
     * @param other Recorder to compare with.
     * @return true if properties match.
     */
    bool operator==(const AudioRecorder& other) const;

    /**
     * @brief Compares two AudioRecorder instances for inequality.
     * @param other Recorder to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const AudioRecorder& other) const;

    /**
     * @brief Stream output operator for formatting AudioRecorder info.
     * @param os Output stream.
     * @param rec Recorder instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioRecorder& rec);

    /**
     * @brief Starts capturing audio samples.
     */
    void StartRecording();

    /**
     * @brief Stops audio recording.
     */
    void StopRecording();

    /**
     * @brief Ingests an incoming audio sample into recording buffer.
     * @param sample Captured AudioSample.
     * @return true if written to buffer.
     */
    bool CaptureSample(const AudioSample& sample);

    /**
     * @brief Resets recording buffer and clears duration counter.
     */
    void Reset();

    /**
     * @brief Gets hardware capture sample rate in Hz.
     * @return Sample rate in Hertz.
     */
    int GetSampleRateHz() const;

    /**
     * @brief Gets total recorded duration in seconds.
     * @return Duration in seconds.
     */
    double GetRecordedSeconds() const;

    /**
     * @brief Checks if recorder is actively capturing audio.
     * @return true if recording.
     */
    bool IsRecording() const;

    /**
     * @brief Gets constant reference to captured AudioBuffer.
     * @return Reference to AudioBuffer.
     */
    const AudioBuffer& GetBuffer() const;

private:
    int sample_rate_hz_;
    double recorded_seconds_;
    bool is_recording_;
    AudioBuffer recorded_buffer_;
};

#endif