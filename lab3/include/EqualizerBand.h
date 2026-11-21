/**
 * @file EqualizerBand.h
 * @brief Declaration of the EqualizerBand class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef EQUALIZERBAND_H
#define EQUALIZERBAND_H

#include <iostream>
#include <string>

/**
 * @brief Represents an individual frequency band in an audio graphic equalizer.
 */
class EqualizerBand {
public:
    /**
     * @brief Constructs an EqualizerBand.
     * @param center_frequency_hz Center frequency in Hertz.
     * @param gain_db Gain in decibels (-12.0 to +12.0 dB).
     * @param q_factor Quality resonance factor.
     * @param is_enabled Band active toggle.
     */
    EqualizerBand(int center_frequency_hz = 1000, double gain_db = 0.0, double q_factor = 1.41, bool is_enabled = true);

    /**
     * @brief Compares two EqualizerBand instances for equality.
     * @param other Band to compare with.
     * @return true if properties match.
     */
    bool operator==(const EqualizerBand& other) const;

    /**
     * @brief Compares two EqualizerBand instances for inequality.
     * @param other Band to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const EqualizerBand& other) const;

    /**
     * @brief Stream output operator for formatting EqualizerBand info.
     * @param os Output stream.
     * @param band Band instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const EqualizerBand& band);

    /**
     * @brief Sets band amplification level.
     * @param gain Gain in decibels.
     * @throws InvalidEqualizerBandException if outside -12 to +12 dB.
     */
    void SetGain(double gain);

    /**
     * @brief Resets gain to 0 dB flat response.
     */
    void Reset();

    /**
     * @brief Sets filter quality resonance factor.
     * @param q Q value.
     */
    void SetQFactor(double q);

    /**
     * @brief Toggles band active status.
     * @param enable Status flag.
     */
    void ToggleBand(bool enable);

    /**
     * @brief Gets center frequency in Hertz.
     * @return Center frequency integer.
     */
    int GetCenterFrequencyHz() const;

    /**
     * @brief Gets current band gain in decibels.
     * @return Gain in dB.
     */
    double GetGainDb() const;

    /**
     * @brief Gets filter resonance Q factor.
     * @return Q factor value.
     */
    double GetQFactor() const;

    /**
     * @brief Checks if band filter is enabled.
     * @return true if enabled.
     */
    bool IsEnabled() const;

private:
    int center_frequency_hz_;
    double gain_db_;
    double q_factor_;
    bool is_enabled_;
};

#endif