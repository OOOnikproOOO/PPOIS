/**
 * @file PitchShifter.h
 * @brief Declaration of the PitchShifter class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PITCHSHIFTER_H
#define PITCHSHIFTER_H

#include <iostream>
#include <string>

/**
 * @brief Real-time musical key pitch shifting and tempo time-stretching controller.
 */
class PitchShifter {
public:
    /**
     * @brief Constructs a PitchShifter.
     * @param semitones_offset Semitone adjustment (-12 to +12).
     * @param tempo_multiplier Speed multiplier (0.5 to 2.0x).
     * @param quality_mode Quality profile ("Standard", "HighQuality").
     * @param is_active Effect enabled flag.
     */
    PitchShifter(int semitones_offset = 0, double tempo_multiplier = 1.0, const std::string& quality_mode = "Standard", bool is_active = false);

    /**
     * @brief Compares two PitchShifter instances for equality.
     * @param other PitchShifter to compare with.
     * @return true if parameters match.
     */
    bool operator==(const PitchShifter& other) const;

    /**
     * @brief Compares two PitchShifter instances for inequality.
     * @param other PitchShifter to compare with.
     * @return true if parameters differ.
     */
    bool operator!=(const PitchShifter& other) const;

    /**
     * @brief Stream output operator for formatting PitchShifter info.
     * @param os Output stream.
     * @param ps PitchShifter instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PitchShifter& ps);

    /**
     * @brief Sets semitone pitch transposition.
     * @param semitones Semitone steps.
     */
    void SetPitchOffset(int semitones);

    /**
     * @brief Sets playback speed tempo without altering pitch.
     * @param tempo Speed factor (0.5 to 2.0).
     */
    void SetTempo(double tempo);

    /**
     * @brief Computes frequency transposition factor from semitones offset.
     * @return Ratio multiplier (e.g. 2.0 for +12 semitones / 1 octave).
     */
    double CalculateFrequencyMultiplier() const;

    /**
     * @brief Resets pitch and tempo back to standard 1.0x values.
     */
    void ResetPitch();

    /**
     * @brief Gets semitone offset (-12 to +12).
     * @return Semitones offset integer.
     */
    int GetSemitonesOffset() const;

    /**
     * @brief Gets tempo time-stretching multiplier.
     * @return Multiplier value.
     */
    double GetTempoMultiplier() const;

    /**
     * @brief Gets quality profile name.
     * @return Reference to quality mode string.
     */
    const std::string& GetQualityMode() const;

    /**
     * @brief Checks if pitch shifting is active.
     * @return true if active.
     */
    bool IsActive() const;

private:
    int semitones_offset_;
    double tempo_multiplier_;
    std::string quality_mode_;
    bool is_active_;
};

#endif