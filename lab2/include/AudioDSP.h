/**
 * @file AudioDSP.h
 * @brief Declaration of the AudioDSP class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIODSP_H
#define AUDIODSP_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a hardware Digital Signal Processor (DSP) applying real-time sound effects.
 */
class AudioDSP {
public:
    /**
     * @brief Constructs an audio DSP coprocessor with standard parameters.
     * @param profile_name Active audio effect preset profile.
     * @param latency_ms Buffer processing latency in milliseconds.
     * @param gain_db Master signal gain in decibels.
     */
    explicit AudioDSP(const std::string& profile_name = "Flat", int latency_ms = 2, double gain_db = 0.0);

    /**
     * @brief Equality operator comparing DSP presets and gain settings.
     * @param other DSP instance to compare.
     * @return true if properties match.
     */
    bool operator==(const AudioDSP& other) const;

    /**
     * @brief Inequality operator.
     * @param other DSP instance to compare.
     * @return true if properties differ.
     */
    bool operator!=(const AudioDSP& other) const;

    /**
     * @brief Stream output operator for formatting DSP state.
     * @param os Output stream.
     * @param dsp AudioDSP instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioDSP& dsp);

    /**
     * @brief Applies a named audio sound profile preset.
     * @param profile Target preset name ("Bass Boost", "Gaming Surround", "Studio Clean").
     */
    void ApplySoundProfile(const std::string& profile);

    /**
     * @brief Adjusts master audio signal gain in decibels.
     * @param gain_db Gain level (-60.0 to +12.0 dB).
     */
    void SetGain(double gain_db);

    /**
     * @brief Toggles equalizer filter processing on or off.
     * @param enable Status flag.
     */
    void ToggleEqualizer(bool enable);

    /**
     * @brief Gets active preset profile name.
     * @return Profile name string.
     */
    std::string GetProfileName() const;

    /**
     * @brief Gets processing latency in milliseconds.
     * @return Latency in ms.
     */
    int GetLatencyMs() const;

    /**
     * @brief Gets current gain level in dB.
     * @return Gain in dB.
     */
    double GetGainDb() const;

    /**
     * @brief Checks if equalizer filter is currently active.
     * @return true if enabled.
     */
    bool IsEqualizerEnabled() const;

private:
    std::string profile_name_;
    int latency_ms_;
    double gain_db_;
    bool equalizer_enabled_;
};

#endif