/**
 * @file AudioDSP.cpp
 * @brief Implementation of AudioDSP methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioDSP.h"
#include "Exceptions.h"

AudioDSP::AudioDSP(const std::string& profile_name, int latency_ms, double gain_db) :
    profile_name_(profile_name), latency_ms_(latency_ms), gain_db_(gain_db), equalizer_enabled_(true) {}

bool AudioDSP::operator==(const AudioDSP& other) const {
    return (profile_name_ == other.profile_name_ &&
            latency_ms_ == other.latency_ms_ &&
            gain_db_ == other.gain_db_ &&
            equalizer_enabled_ == other.equalizer_enabled_);
}

bool AudioDSP::operator!=(const AudioDSP& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioDSP& dsp) {
    os << "AudioDSP [Profile: " << dsp.profile_name_ << ", Gain: " << dsp.gain_db_ << " dB, Latency: " << dsp.latency_ms_ << " ms, EQ: " << (dsp.equalizer_enabled_ ? "ON" : "OFF") << "]";
    return os;
}

void AudioDSP::ApplySoundProfile(const std::string& profile) {
    if (profile.empty())
        throw ComputerException("Sound profile name cannot be empty.");
    
    profile_name_ = profile;
}

void AudioDSP::SetGain(double gain_db) {
    if (gain_db < -60.0 || gain_db > 12.0)
        throw ComputerException("Audio DSP gain out of safe range (-60.0 dB to +12.0 dB).");
    
    gain_db_ = gain_db;
}

void AudioDSP::ToggleEqualizer(bool enable) {
    equalizer_enabled_ = enable;
}

std::string AudioDSP::GetProfileName() const {
    return profile_name_;
}

int AudioDSP::GetLatencyMs() const {
    return latency_ms_;
}

double AudioDSP::GetGainDb() const {
    return gain_db_;
}

bool AudioDSP::IsEqualizerEnabled() const {
    return equalizer_enabled_;
}