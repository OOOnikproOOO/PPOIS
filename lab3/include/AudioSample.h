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

    /**
     * @brief Compares two AudioSample instances for equality.
     * @param other Sample to compare with.
     * @return true if amplitudes and bit depth match.
     */
    bool operator==(const AudioSample& other) const;

    /**
     * @brief Compares two AudioSample instances for inequality.
     * @param other Sample to compare with.
     * @return true if amplitudes or bit depth differ.
     */
    bool operator!=(const AudioSample& other) const;

    /**
     * @brief Stream output operator for formatting AudioSample info.
     * @param os Output stream.
     * @param sample Sample instance to display.
     * @return Reference to the output stream.
     */
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

    /**
     * @brief Gets left channel amplitude.
     * @return Left channel value.
     */
    double GetLeftChannel() const;

    /**
     * @brief Gets right channel amplitude.
     * @return Right channel value.
     */
    double GetRightChannel() const;

    /**
     * @brief Gets bit depth resolution.
     * @return Bit depth integer (16, 24, 32).
     */
    int GetBitDepth() const;

    /**
     * @brief Checks if sample experienced amplitude clipping.
     * @return true if clipped.
     */
    bool IsClipped() const;

private:
    double left_channel_;
    double right_channel_;
    int bit_depth_;
    bool is_clipped_;
};

#endif