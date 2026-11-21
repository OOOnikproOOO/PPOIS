/**
 * @file BassBoostEffect.h
 * @brief Declaration of the BassBoostEffect class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef BASSBOOSTEFFECT_H
#define BASSBOOSTEFFECT_H

#include <iostream>

/**
 * @brief Low-frequency enhancement DSP effect.
 */
class BassBoostEffect {
public:
    /**
     * @brief Constructs a BassBoostEffect.
     * @param boost_db Bass amplification gain in decibels (0.0 to 18.0 dB).
     * @param cutoff_frequency_hz Low-pass shelf frequency (40 to 250 Hz).
     * @param is_active Effect enabled flag.
     */
    BassBoostEffect(double boost_db = 6.0, int cutoff_frequency_hz = 120, bool is_active = false);

    /**
     * @brief Compares two BassBoostEffect instances for equality.
     * @param other Effect to compare with.
     * @return true if parameters match.
     */
    bool operator==(const BassBoostEffect& other) const;

    /**
     * @brief Compares two BassBoostEffect instances for inequality.
     * @param other Effect to compare with.
     * @return true if parameters differ.
     */
    bool operator!=(const BassBoostEffect& other) const;

    /**
     * @brief Stream output operator for formatting BassBoostEffect info.
     * @param os Output stream.
     * @param effect Effect instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const BassBoostEffect& effect);

    /**
     * @brief Sets bass gain level.
     * @param db Decibels.
     */
    void SetBoost(double db);

    /**
     * @brief Sets frequency cutoff in Hz.
     * @param hz Cutoff frequency.
     */
    void SetCutoff(int hz);

    /**
     * @brief Applies bass gain to sample.
     * @param sample_amplitude Input signal amplitude.
     * @return Output processed amplitude.
     */
    double ApplyBassBoost(double sample_amplitude) const;

    /**
     * @brief Toggles effect processing.
     * @param active State.
     */
    void ToggleEffect(bool active);

    /**
     * @brief Gets current bass boost gain in dB.
     * @return Gain in decibels.
     */
    double GetBoostDb() const;

    /**
     * @brief Gets low-pass shelf cutoff frequency.
     * @return Frequency in Hz.
     */
    int GetCutoffFrequencyHz() const;

    /**
     * @brief Checks if effect is currently active.
     * @return true if active.
     */
    bool IsActive() const;

private:
    double boost_db_;
    int cutoff_frequency_hz_;
    bool is_active_;
};

#endif