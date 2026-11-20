/**
 * @file SpectrumAnalyzer.h
 * @brief Declaration of the SpectrumAnalyzer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SPECTRUMANALYZER_H
#define SPECTRUMANALYZER_H

#include <iostream>
#include <vector>
#include "AudioBuffer.h"

/**
 * @brief Fast audio frequency spectrum energy analyzer for visual meters and equalizer visualizations.
 */
class SpectrumAnalyzer {
public:
    /**
     * @brief Constructs a SpectrumAnalyzer.
     * @param bands_count Number of frequency analysis bins (e.g. 8, 16, 32).
     * @param peak_decay_rate Falloff rate per frame (0.01 to 0.5).
     * @param is_active Analyzer enabled flag.
     */
    SpectrumAnalyzer(size_t bands_count = 16, double peak_decay_rate = 0.05, bool is_active = true);

    /**
     * @brief Compares two SpectrumAnalyzer instances for equality.
     * @param other Analyzer to compare with.
     * @return true if properties match.
     */
    bool operator==(const SpectrumAnalyzer& other) const;

    /**
     * @brief Compares two SpectrumAnalyzer instances for inequality.
     * @param other Analyzer to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const SpectrumAnalyzer& other) const;

    /**
     * @brief Stream output operator for formatting SpectrumAnalyzer info.
     * @param os Output stream.
     * @param analyzer Analyzer instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SpectrumAnalyzer& analyzer);

    /**
     * @brief Computes frequency band energy distribution from incoming PCM audio samples.
     * @param buffer Source AudioBuffer containing samples.
     */
    void ProcessBuffer(const AudioBuffer& buffer);

    /**
     * @brief Retrieves calculated energy level for a specific frequency band.
     * @param band_index Zero-based band index.
     * @return Energy level normalized between 0.0 and 1.0.
     */
    double GetBandEnergy(size_t band_index) const;

    /**
     * @brief Calculates total combined spectral power across all bands.
     * @return Sum of band energies.
     */
    double CalculateTotalEnergy() const;

    /**
     * @brief Clears band energies and resets decay state.
     */
    void Reset();

    /**
     * @brief Toggles spectrum analyzer processing.
     * @param active State.
     */
    void ToggleActive(bool active);

    /**
     * @brief Gets number of frequency spectrum bands.
     * @return Count of bands.
     */
    size_t GetBandsCount() const;

    /**
     * @brief Gets peak decay falloff rate.
     * @return Decay rate.
     */
    double GetPeakDecayRate() const;

    /**
     * @brief Checks if spectrum analyzer is active.
     * @return true if active.
     */
    bool IsActive() const;

    /**
     * @brief Gets constant reference to energy array across all frequency bands.
     * @return Reference to vector of band energies.
     */
    const std::vector<double>& GetBandEnergies() const;

private:
    size_t bands_count_;
    double peak_decay_rate_;
    bool is_active_;
    std::vector<double> band_energies_;
};

#endif