/**
 * @file PlaybackPosition.cpp
 * @brief Implementation of PlaybackPosition methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PlaybackPosition.h"
#include <iomanip>
#include <sstream>
#include <cmath>

PlaybackPosition::PlaybackPosition(double total_sec, double current_sec, double playback_speed) :
    current_sec_(current_sec >= 0.0 ? current_sec : 0.0), total_sec_(total_sec > 0.0 ? total_sec : 1.0), is_seeking_(false), playback_speed_(playback_speed > 0.1 ? playback_speed : 1.0) {}

bool PlaybackPosition::operator==(const PlaybackPosition& other) const {
    const double kEpsilon = 1e-4;
    return std::abs(current_sec_ - other.current_sec_) < kEpsilon &&
           std::abs(total_sec_ - other.total_sec_) < kEpsilon &&
           is_seeking_ == other.is_seeking_ &&
           std::abs(playback_speed_ - other.playback_speed_) < kEpsilon;
}

bool PlaybackPosition::operator!=(const PlaybackPosition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PlaybackPosition& pos) {
    os << "Position[" << pos.FormatTimeElapsed() << ", " << pos.playback_speed_ << "x]";
    return os;
}

void PlaybackPosition::Advance(double delta_sec) {
    if (delta_sec <= 0.0)
        return;
    
    current_sec_ += delta_sec * playback_speed_;
    if (current_sec_ > total_sec_)
        current_sec_ = total_sec_;
}

void PlaybackPosition::SeekTo(double target_sec) {
    is_seeking_ = true;
    if (target_sec < 0.0)
        current_sec_ = 0.0;
    else if (target_sec > total_sec_)
        current_sec_ = total_sec_;
    else
        current_sec_ = target_sec;
    
    is_seeking_ = false;
}

double PlaybackPosition::CalculateProgressPercent() const {
    if (total_sec_ <= 0.0)
        return 0.0;
    
    return (current_sec_ / total_sec_) * 100;
}

std::string PlaybackPosition::FormatTimeElapsed() const {
    int cur_tot = static_cast<int>(current_sec_);
    int cur_m = cur_tot / 60;
    int cur_s = cur_tot % 60;

    int max_tot = static_cast<int>(total_sec_);
    int max_m = max_tot / 60;
    int max_s = max_tot % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << cur_m << ":"
        << std::setfill('0') << std::setw(2) << cur_s << " / "
        << std::setfill('0') << std::setw(2) << max_m << ":"
        << std::setfill('0') << std::setw(2) << max_s;
    return oss.str();
}

void PlaybackPosition::Reset() {
    current_sec_ = 0.0;
    is_seeking_ = false;
}

double PlaybackPosition::GetCurrentSec() const {
    return current_sec_;
}

double PlaybackPosition::GetTotalSec() const {
    return total_sec_;
}

double PlaybackPosition::GetPlaybackSpeed() const {
    return playback_speed_;
}

bool PlaybackPosition::IsAtEnd() const {
    return current_sec_ >= total_sec_;
}