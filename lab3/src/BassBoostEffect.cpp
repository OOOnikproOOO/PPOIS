/**
 * @file BassBoostEffect.cpp
 * @brief Implementation of BassBoostEffect methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "BassBoostEffect.h"
#include <cmath>

BassBoostEffect::BassBoostEffect(double boost_db, int cutoff_frequency_hz, bool is_active) :
    boost_db_(boost_db > 18.0 ? 18.0 : (boost_db < 0.0 ? 0.0 : boost_db)),
    cutoff_frequency_hz_(cutoff_frequency_hz > 250 ? 250 : (cutoff_frequency_hz < 40 ? 40 : cutoff_frequency_hz)),
    is_active_(is_active) {}

bool BassBoostEffect::operator==(const BassBoostEffect& other) const {
    const double kEpsilon = 1e-4;
    return std::abs(boost_db_ - other.boost_db_) < kEpsilon &&
           cutoff_frequency_hz_ == other.cutoff_frequency_hz_ &&
           is_active_ == other.is_active_;
}

bool BassBoostEffect::operator!=(const BassBoostEffect& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const BassBoostEffect& effect) {
    os << "BassBoost[+" << effect.boost_db_ << " dB below " << effect.cutoff_frequency_hz_ << " Hz (" << (effect.is_active_ ? "ON" : "OFF") << ")]";
    return os;
}

void BassBoostEffect::SetBoost(double db) {
    if (db < 0.0)
        db = 0.0;

    if (db > 18.0)
        db = 18.0;

    boost_db_ = db;
}

void BassBoostEffect::SetCutoff(int hz) {
    if (hz >= 40 && hz <= 250)
        cutoff_frequency_hz_ = hz;
}

double BassBoostEffect::ApplyBassBoost(double sample_amplitude) const {
    if (!is_active_)
        return sample_amplitude;

    double linear_gain = std::pow(10.0, boost_db_ / 20);
    return sample_amplitude * linear_gain;
}

void BassBoostEffect::ToggleEffect(bool active) {
    is_active_ = active;
}

double BassBoostEffect::GetBoostDb() const {
    return boost_db_;
}

int BassBoostEffect::GetCutoffFrequencyHz() const {
    return cutoff_frequency_hz_;
}

bool BassBoostEffect::IsActive() const {
    return is_active_;
}