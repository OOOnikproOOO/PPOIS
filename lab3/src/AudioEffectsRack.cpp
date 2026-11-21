/**
 * @file AudioEffectsRack.cpp
 * @brief Implementation of AudioEffectsRack methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioEffectsRack.h"

AudioEffectsRack::AudioEffectsRack(bool is_bypass, const GraphicEqualizer& equalizer, const ReverbEffect& reverb, const BassBoostEffect& bass_boost, const PitchShifter& pitch) :
    is_bypass_(is_bypass), equalizer_(equalizer), reverb_(reverb), bass_boost_(bass_boost), pitch_(pitch) {}

bool AudioEffectsRack::operator==(const AudioEffectsRack& other) const {
    return is_bypass_ == other.is_bypass_ &&
           equalizer_ == other.equalizer_ &&
           reverb_ == other.reverb_ &&
           bass_boost_ == other.bass_boost_ &&
           pitch_ == other.pitch_;
}

bool AudioEffectsRack::operator!=(const AudioEffectsRack& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioEffectsRack& rack) {
    os << "EffectsRack[" << (rack.is_bypass_ ? "BYPASS" : "ACTIVE") << ", HasActive: " << (rack.HasActiveEffects() ? "Yes" : "No") << "]";
    return os;
}

void AudioEffectsRack::SetBypassAll(bool bypass) {
    is_bypass_ = bypass;
}

void AudioEffectsRack::ResetAllEffects() {
    equalizer_.ResetAllBands();
    reverb_.ToggleEffect(false);
    bass_boost_.ToggleEffect(false);
    pitch_.ResetPitch();
    is_bypass_ = false;
}

bool AudioEffectsRack::HasActiveEffects() const {
    if (is_bypass_)
        return false;
    
    return equalizer_.IsActive() || reverb_.IsActive() || bass_boost_.IsActive() || pitch_.IsActive();
}

bool AudioEffectsRack::IsBypass() const {
    return is_bypass_;
}

GraphicEqualizer& AudioEffectsRack::GetEqualizer() {
    return equalizer_;
}

const GraphicEqualizer& AudioEffectsRack::GetEqualizer() const {
    return equalizer_;
}

ReverbEffect& AudioEffectsRack::GetReverb() {
    return reverb_;
}

const ReverbEffect& AudioEffectsRack::GetReverb() const {
    return reverb_;
}

BassBoostEffect& AudioEffectsRack::GetBassBoost() {
    return bass_boost_;
}

const BassBoostEffect& AudioEffectsRack::GetBassBoost() const {
    return bass_boost_;
}

PitchShifter& AudioEffectsRack::GetPitch() {
    return pitch_;
}

const PitchShifter& AudioEffectsRack::GetPitch() const {
    return pitch_;
}