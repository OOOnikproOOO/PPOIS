/**
 * @file AudioVisualizer.h
 * @brief Declaration of the AudioVisualizer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOVISUALIZER_H
#define AUDIOVISUALIZER_H

#include <iostream>
#include <string>
#include "AudioSample.h"

/**
 * @brief Generates text and console visual representations of stereo sound meters (VU meters, peak indicators).
 */
class AudioVisualizer {
public:
    /**
     * @brief Constructs an AudioVisualizer.
     * @param mode Visualization mode ("VU_Meter", "Waveform", "SpectrumBars").
     * @param refresh_rate_hz Visualizer refresh rate in Hz (10 to 120).
     */
    AudioVisualizer(const std::string& mode = "VU_Meter", int refresh_rate_hz = 60);

    /**
     * @brief Compares two AudioVisualizer instances for equality.
     * @param other Visualizer to compare with.
     * @return true if mode and parameters match.
     */
    bool operator==(const AudioVisualizer& other) const;

    /**
     * @brief Compares two AudioVisualizer instances for inequality.
     * @param other Visualizer to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const AudioVisualizer& other) const;

    /**
     * @brief Stream output operator for formatting AudioVisualizer info.
     * @param os Output stream.
     * @param viz Visualizer instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioVisualizer& viz);

    /**
     * @brief Feeds a stereo sample to update peak and RMS levels.
     * @param sample AudioSample to analyze.
     */
    void UpdateLevels(const AudioSample& sample);

    /**
     * @brief Generates an ASCII horizontal bar meter representation of amplitude.
     * @param level Normalized signal level (0.0 to 1.0).
     * @param bar_width Total character width.
     * @return String visual bar e.g. '[========    ]'.
     */
    std::string RenderAsciiBar(double level, int bar_width = 15) const;

    /**
     * @brief Formats dual-channel stereo VU meter as text string.
     * @return Formatted stereo meter string.
     */
    std::string RenderStereoVuMeter() const;

    /**
     * @brief Resets peak hold levels to zero.
     */
    void ResetPeaks();

    /**
     * @brief Sets visualization display mode.
     * @param mode Target mode string.
     */
    void SetMode(const std::string& mode);

    /**
     * @brief Gets current visualization mode name.
     * @return Reference to mode string.
     */
    const std::string& GetMode() const;

    /**
     * @brief Gets highest recorded left channel peak level.
     * @return Left peak value (0.0 to 1.0).
     */
    double GetLeftPeak() const;

    /**
     * @brief Gets highest recorded right channel peak level.
     * @return Right peak value (0.0 to 1.0).
     */
    double GetRightPeak() const;

    /**
     * @brief Gets refresh rate frequency in Hz.
     * @return Refresh rate in Hertz.
     */
    int GetRefreshRateHz() const;

private:
    std::string visualization_mode_;
    double left_peak_;
    double right_peak_;
    int refresh_rate_hz_;
};

#endif