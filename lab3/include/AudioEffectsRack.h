/**
 * @file AudioEffectsRack.h
 * @brief Declaration of the AudioEffectsRack class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOEFFECTSRACK_H
#define AUDIOEFFECTSRACK_H

#include <iostream>
#include "GraphicEqualizer.h"
#include "ReverbEffect.h"
#include "BassBoostEffect.h"
#include "PitchShifter.h"

/**
 * @brief Modular DSP effects rack chaining EQ, reverb, bass boost, and pitch transposition.
 */
class AudioEffectsRack {
public:
    /**
     * @brief Constructs an AudioEffectsRack.
     * @param is_bypass Master bypass status.
     * @param equalizer Graphic equalizer.
     * @param reverb Reverb processor.
     * @param bass_boost Bass boost effect.
     * @param pitch Pitch shifter.
     */
    AudioEffectsRack(bool is_bypass = false, const GraphicEqualizer& equalizer = GraphicEqualizer(), const ReverbEffect& reverb = ReverbEffect(), const BassBoostEffect& bass_boost = BassBoostEffect(), const PitchShifter& pitch = PitchShifter());

    /**
     * @brief Compares two AudioEffectsRack instances for equality.
     * @param other Rack to compare with.
     * @return true if bypass and all inner effects match.
     */
    bool operator==(const AudioEffectsRack& other) const;

    /**
     * @brief Compares two AudioEffectsRack instances for inequality.
     * @param other Rack to compare with.
     * @return true if parameters differ.
     */
    bool operator!=(const AudioEffectsRack& other) const;

    /**
     * @brief Stream output operator for formatting AudioEffectsRack info.
     * @param os Output stream.
     * @param rack Rack instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioEffectsRack& rack);

    /**
     * @brief Toggles master bypass across entire effects rack.
     * @param bypass Bypass flag.
     */
    void SetBypassAll(bool bypass);

    /**
     * @brief Resets all effects to default flat neutral states.
     */
    void ResetAllEffects();

    /**
     * @brief Checks if any effect in the rack is actively modifying the audio signal.
     * @return true if at least one effect is enabled.
     */
    bool HasActiveEffects() const;

    /**
     * @brief Checks if master rack bypass is enabled.
     * @return true if bypass is active.
     */
    bool IsBypass() const;

    /**
     * @brief Gets mutable reference to GraphicEqualizer.
     * @return Reference to GraphicEqualizer.
     */
    GraphicEqualizer& GetEqualizer();

    /**
     * @brief Gets constant reference to GraphicEqualizer.
     * @return Const reference to GraphicEqualizer.
     */
    const GraphicEqualizer& GetEqualizer() const;

    /**
     * @brief Gets mutable reference to ReverbEffect.
     * @return Reference to ReverbEffect.
     */
    ReverbEffect& GetReverb();

    /**
     * @brief Gets constant reference to ReverbEffect.
     * @return Const reference to ReverbEffect.
     */
    const ReverbEffect& GetReverb() const;

    /**
     * @brief Gets mutable reference to BassBoostEffect.
     * @return Reference to BassBoostEffect.
     */
    BassBoostEffect& GetBassBoost();

    /**
     * @brief Gets constant reference to BassBoostEffect.
     * @return Const reference to BassBoostEffect.
     */
    const BassBoostEffect& GetBassBoost() const;

    /**
     * @brief Gets mutable reference to PitchShifter.
     * @return Reference to PitchShifter.
     */
    PitchShifter& GetPitch();

    /**
     * @brief Gets constant reference to PitchShifter.
     * @return Const reference to PitchShifter.
     */
    const PitchShifter& GetPitch() const;

private:
    bool is_bypass_;
    GraphicEqualizer equalizer_;
    ReverbEffect reverb_;
    BassBoostEffect bass_boost_;
    PitchShifter pitch_;
};

#endif