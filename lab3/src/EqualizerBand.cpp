/**
 * @file EqualizerBand.cpp
 * @brief Implementation of EqualizerBand methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "EqualizerBand.h"
#include "InvalidEqualizerBandException.h"
#include <cmath>

EqualizerBand::EqualizerBand(int center_frequency_hz, double gain_db, double q_factor, bool is_enabled) :
    center_frequency_hz_(center_frequency_hz), gain_db_(gain_db), q_factor_(q_factor), is_enabled_(is_enabled) {}

bool EqualizerBand::operator==(const EqualizerBand& other) const {
    const double kEpsilon = 1e-4;
    return center_frequency_hz_ == other.center_frequency_hz_ &&
           std::abs(gain_db_ - other.gain_db_) < kEpsilon &&
           std::abs(q_factor_ - other.q_factor_) < kEpsilon &&
           is_enabled_ == other.is_enabled_;
}

bool EqualizerBand::operator!=(const EqualizerBand& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const EqualizerBand& band) {
    os << "Band[" << band.center_frequency_hz_ << " Hz: " << band.gain_db_ << " dB (" << (band.is_enabled_ ? "ON" : "OFF") << ")]";
    return os;
}

void EqualizerBand::SetGain(double gain) {
    const double kMinGain = -12.0;
    const double kMaxGain = 12.0;
    if (gain < kMinGain || gain > kMaxGain)
        throw InvalidEqualizerBandException("Equalizer band gain " + std::to_string(gain) + " dB out of bounds [-12, +12].");
    
    gain_db_ = gain;
}

void EqualizerBand::Reset() {
    gain_db_ = 0.0;
}

void EqualizerBand::SetQFactor(double q) {
    const double kMinQ = 0.1;
    const double kMaxQ = 10.0;
    if (q >= kMinQ && q <= kMaxQ)
        q_factor_ = q;
}

void EqualizerBand::ToggleBand(bool enable) {
    is_enabled_ = enable;
}

int EqualizerBand::GetCenterFrequencyHz() const {
    return center_frequency_hz_;
}

double EqualizerBand::GetGainDb() const {
    return gain_db_;
}

double EqualizerBand::GetQFactor() const {
    return q_factor_;
}

bool EqualizerBand::IsEnabled() const {
    return is_enabled_;
}