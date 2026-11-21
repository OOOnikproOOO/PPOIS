/**
 * @file ReverbEffect.cpp
 * @brief Implementation of ReverbEffect methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ReverbEffect.h"
#include <cmath>

ReverbEffect::ReverbEffect(double room_size, double damping, double wet_level, bool is_active) :
    room_size_(room_size > 1.0 ? 1.0 : (room_size < 0.0 ? 0.0 : room_size)), damping_(damping > 1.0 ? 1.0 : (damping < 0.0 ? 0.0 : damping)), wet_level_(wet_level > 1.0 ? 1.0 : (wet_level < 0.0 ? 0.0 : wet_level)), is_active_(is_active) {}

bool ReverbEffect::operator==(const ReverbEffect& other) const {
    const double kEpsilon = 1e-4;
    return std::abs(room_size_ - other.room_size_) < kEpsilon &&
           std::abs(damping_ - other.damping_) < kEpsilon &&
           std::abs(wet_level_ - other.wet_level_) < kEpsilon &&
           is_active_ == other.is_active_;
}

bool ReverbEffect::operator!=(const ReverbEffect& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const ReverbEffect& effect) {
    os << "Reverb[Room: " << effect.room_size_ << ", Wet: " << effect.wet_level_ << " (" << (effect.is_active_ ? "Active" : "Bypass") << ")]";
    return os;
}

double ReverbEffect::ProcessSample(double input_amplitude) const {
    if (!is_active_)
        return input_amplitude;
    
    double simulated_echo = input_amplitude * room_size_ * (1.0 - damping_);
    return (1.0 - wet_level_) * input_amplitude + wet_level_ * simulated_echo;
}

void ReverbEffect::SetRoomSize(double size) {
    if (size >= 0.0 && size <= 1.0)
        room_size_ = size;
}

void ReverbEffect::SetDamping(double damp) {
    if (damp >= 0.0 && damp <= 1.0)
        damping_ = damp;
}

void ReverbEffect::SetWetLevel(double wet) {
    if (wet >= 0.0 && wet <= 1.0)
        wet_level_ = wet;
}

void ReverbEffect::ToggleEffect(bool active) {
    is_active_ = active;
}

double ReverbEffect::GetRoomSize() const {
    return room_size_;
}

double ReverbEffect::GetDamping() const {
    return damping_;
}

double ReverbEffect::GetWetLevel() const {
    return wet_level_;
}

bool ReverbEffect::IsActive() const {
    return is_active_;
}