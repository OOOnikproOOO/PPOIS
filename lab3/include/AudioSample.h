/**
 * @file AudioSample.h
 * @brief Declaration of the AudioSample class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOSAMPLE_H
#define AUDIOSAMPLE_H

#include <iostream>

/**
 * @brief Represents a stereo PCM audio sample with amplitude normalization.
 */
class AudioSample {
public:
    /**
     * @brief Constructs an AudioSample.
     * @param left Left channel amplitude (-1.0 to 1.0).
     * @param right Right channel amplitude (-1.0 to 1.0).
     * @param bit_depth Bit resolution (16, 24, 32).
     */
    AudioSample(double left = 0.0, double right = 0.0, int bit_depth = 16);

    bool operator==(const AudioSample& other) const;
    bool operator!=(const AudioSample& other) const;
    friend std::ostream& operator<<(std::ostream& os, const AudioSample& sample);

    /**
     * @brief Amplifies sample channels by a multiplier factor.
     * @param factor Gain multiplier.
     */
    void Amplify(double factor);

    /**
     * @brief Clamps channel amplitudes within safe boundaries to prevent clipping distortion.
     * @param peak_limit Maximum allowed absolute amplitude.
     */
    void Normalize(double peak_limit);

    /**
     * @brief Downmixes stereo channels into a single mono signal across both channels.
     */
    void ConvertToMono();

    /**
     * @brief Computes Root Mean Square (RMS) energy power of the sample.
     * @return RMS power value.
     */
    double CalculatePowerRms() const;

    double GetLeftChannel() const;
    double GetRightChannel() const;
    int GetBitDepth() const;
    bool IsClipped() const;

private:
    double left_channel_;
    double right_channel_;
    int bit_depth_;
    bool is_clipped_;
};

#endif