/**
 * @file CrossfadeEngine.cpp
 * @brief Implementation of CrossfadeEngine methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "CrossfadeEngine.h"
#include <cmath>

CrossfadeEngine::CrossfadeEngine(double duration_sec, bool is_enabled, const std::string& transition_curve) :
    duration_sec_(duration_sec > 0.0 ? duration_sec : 4.0), is_enabled_(is_enabled), transition_curve_(transition_curve) {}

bool CrossfadeEngine::operator==(const CrossfadeEngine& other) const {
    const double kEpsilon = 1e-4;
    return std::abs(duration_sec_ - other.duration_sec_) < kEpsilon &&
           is_enabled_ == other.is_enabled_ &&
           transition_curve_ == other.transition_curve_;
}

bool CrossfadeEngine::operator!=(const CrossfadeEngine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CrossfadeEngine& engine) {
    os << "Crossfade[" << engine.duration_sec_ << "s, " << engine.transition_curve_ << " (" << (engine.is_enabled_ ? "ON" : "OFF") << ")]";
    return os;
}

void CrossfadeEngine::CalculateMixCoefficients(double current_crossfade_time, double& out_track1_vol, double& out_track2_vol) const {
    if (!is_enabled_ || duration_sec_ <= 0.0) {
        out_track1_vol = 0.0;
        out_track2_vol = 1.0;
        return;
    }

    double progress = current_crossfade_time / duration_sec_;
    if (progress < 0.0)
        progress = 0.0;
    
    if (progress > 1.0)
        progress = 1.0;

    if (transition_curve_ == "Linear") {
        out_track1_vol = 1.0 - progress;
        out_track2_vol = progress;
    } else {
        const double Pi = 3.141592653589;
        out_track1_vol = std::cos(progress * 0.5 * Pi);
        out_track2_vol = std::sin(progress * 0.5 * Pi);
    }
}

void CrossfadeEngine::SetDuration(double sec) {
    const double kMinDuration = 0.5;
    const double kMaxDuration = 15.0;
    if (sec >= kMinDuration && sec <= kMaxDuration)
        duration_sec_ = sec;
}

void CrossfadeEngine::ToggleCrossfade(bool enable) {
    is_enabled_ = enable;
}

void CrossfadeEngine::SetCurve(const std::string& curve) {
    if (curve == "Linear" || curve == "EqualPower" || curve == "Exponential")
        transition_curve_ = curve;
}

double CrossfadeEngine::GetDurationSec() const {
    return duration_sec_;
}

bool CrossfadeEngine::IsEnabled() const {
    return is_enabled_;
}

const std::string& CrossfadeEngine::GetTransitionCurve() const {
    return transition_curve_;
}