/**
 * @file AudioDAC.h
 * @brief Declaration of the AudioDAC class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIODAC_H
#define AUDIODAC_H

#include <iostream>

/**
 * @brief Class modeling an electronic Digital-to-Analog Converter (DAC) chip for sound generation.
 */
class AudioDAC {
public:
    /**
     * @brief Constructs an Audio DAC with specified sampling rate and bit resolution.
     * @param sampling_rate_hz Audio sample rate in Hz (e.g. 48000, 96000, 192000).
     * @param bit_depth Bit resolution depth (e.g. 16, 24, 32).
     * @param snr_db Signal-to-Noise Ratio in decibels.
     */
    explicit AudioDAC(int sampling_rate_hz = 48000, int bit_depth = 24, double snr_db = 115.0);

    /**
     * @brief Compares two DACs for equality based on operational format and SNR.
     * @param other DAC to compare with.
     * @return true if properties match.
     */
    bool operator==(const AudioDAC& other) const;

    /**
     * @brief Inequality operator.
     * @param other DAC to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const AudioDAC& other) const;

    /**
     * @brief Stream output operator for formatting DAC status.
     * @param os Output stream.
     * @param dac AudioDAC instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioDAC& dac);

    /**
     * @brief Converts digital audio PCM samples into analog electrical output signal.
     * @param sample_count Number of digital samples to process.
     * @return true on successful playback conversion.
     */
    bool ConvertDigitalToAnalog(int sample_count);

    /**
     * @brief Configures DAC playback format parameters.
     * @param sampling_rate_hz Target sample frequency.
     * @param bit_depth Target bit resolution.
     */
    void SetFormat(int sampling_rate_hz, int bit_depth);

    /**
     * @brief Computes theoretical dynamic range in decibels.
     * @return Dynamic range in dB.
     */
    double CalculateDynamicRangeDb() const;

    /**
     * @brief Gets current sampling rate in Hz.
     * @return Sampling frequency.
     */
    int GetSamplingRateHz() const;

    /**
     * @brief Gets bit depth resolution.
     * @return Bit depth.
     */
    int GetBitDepth() const;

    /**
     * @brief Gets signal-to-noise ratio in dB.
     * @return SNR in dB.
     */
    double GetSnrDb() const;

    /**
     * @brief Checks if DAC is currently powered and active.
     * @return true if active.
     */
    bool IsActive() const;

private:
    int sampling_rate_hz_;
    int bit_depth_;
    double snr_db_;
    bool is_active_;
};

#endif