/**
 * @file VolumeControl.cpp
 * @brief Implementation of VolumeControl methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "VolumeControl.h"
#include <cmath>

VolumeControl::VolumeControl(int volume_level, bool is_muted, int max_limit) :
    volume_level_(volume_level > 100 ? 100 : (volume_level < 0 ? 0 : volume_level)), is_muted_(is_muted), saved_volume_(volume_level_), max_limit_(max_limit > 100 ? 100 : (max_limit < 10 ? 10 : max_limit)) {}

bool VolumeControl::operator==(const VolumeControl& other) const {
    return volume_level_ == other.volume_level_ &&
           is_muted_ == other.is_muted_ &&
           saved_volume_ == other.saved_volume_ &&
           max_limit_ == other.max_limit_;
}

bool VolumeControl::operator!=(const VolumeControl& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const VolumeControl& vc) {
    os << "Volume[" << (vc.is_muted_ ? "MUTED" : std::to_string(vc.volume_level_) + "%") << ", Limit: " << vc.max_limit_ << "%]";
    return os;
}

void VolumeControl::SetVolume(int level) {
    if (level < 0)
        level = 0;
    
    if (level > max_limit_)
        level = max_limit_;
    
    volume_level_ = level;
    saved_volume_ = level;
    if (is_muted_ && level > 0)
        is_muted_ = false;
}

void VolumeControl::ToggleMute() {
    if (is_muted_) {
        is_muted_ = false;
        volume_level_ = saved_volume_;
    } else {
        saved_volume_ = volume_level_;
        volume_level_ = 0;
        is_muted_ = true;
    }
}

double VolumeControl::CalculateGainDecibels() const {
    int eff = GetEffectiveVolume();
    if (eff <= 0)
        return -60.0;

    double linear = static_cast<double>(eff) / 100.0;
    if (linear <= 0.0)
        return -60.0;

    return 20.0 * std::log10(linear);
}

void VolumeControl::SetMaxLimit(int limit) {
    if (limit < 10)
        limit = 10;
    
    if (limit > 100)
        limit = 100;
    
    max_limit_ = limit;
    if (volume_level_ > max_limit_)
        volume_level_ = max_limit_;
}

void VolumeControl::Reset() {
    volume_level_ = 50;
    saved_volume_ = 50;
    is_muted_ = false;
    max_limit_ = 100;
}

int VolumeControl::GetVolumeLevel() const {
    return volume_level_;
}

bool VolumeControl::IsMuted() const {
    return is_muted_;
}

int VolumeControl::GetMaxLimit() const {
    return max_limit_;
}

int VolumeControl::GetEffectiveVolume() const {
    if (is_muted_)
        return 0;
    
    return volume_level_;
}