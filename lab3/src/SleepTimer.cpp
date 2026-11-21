/**
 * @file SleepTimer.cpp
 * @brief Implementation of SleepTimer methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SleepTimer.h"

SleepTimer::SleepTimer(int duration_minutes, int fadeout_duration_sec, bool should_fadeout, bool is_active) :
    duration_minutes_(duration_minutes < 1 ? 1 : duration_minutes), remaining_minutes_(duration_minutes_), fadeout_duration_sec_(fadeout_duration_sec < 0 ? 0 : fadeout_duration_sec), should_fadeout_(should_fadeout), is_active_(is_active) {}

bool SleepTimer::operator==(const SleepTimer& other) const {
    return duration_minutes_ == other.duration_minutes_ &&
           remaining_minutes_ == other.remaining_minutes_ &&
           fadeout_duration_sec_ == other.fadeout_duration_sec_ &&
           should_fadeout_ == other.should_fadeout_ &&
           is_active_ == other.is_active_;
}

bool SleepTimer::operator!=(const SleepTimer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SleepTimer& timer) {
    os << "SleepTimer[" << (timer.is_active_ ? "ACTIVE" : "OFF") << ", Remaining: " << timer.remaining_minutes_ << "m/" << timer.duration_minutes_ << "m]";
    return os;
}

void SleepTimer::Start(int minutes, bool fadeout) {
    if (minutes < 1)
        minutes = 1;

    duration_minutes_ = minutes;
    remaining_minutes_ = minutes;
    should_fadeout_ = fadeout;
    is_active_ = true;
}

void SleepTimer::TickMinutes(int elapsed_minutes) {
    if (!is_active_)
        return;

    remaining_minutes_ -= elapsed_minutes;
    if (remaining_minutes_ <= 0) {
        remaining_minutes_ = 0;
        is_active_ = false;
    }
}

void SleepTimer::Cancel() {
    is_active_ = false;
    remaining_minutes_ = 0;
}

bool SleepTimer::IsExpired() const {
    return !is_active_ && remaining_minutes_ == 0;
}

int SleepTimer::GetRemainingMinutes() const {
    return remaining_minutes_;
}

int SleepTimer::GetFadeoutDurationSec() const {
    return fadeout_duration_sec_;
}

bool SleepTimer::ShouldFadeout() const {
    return should_fadeout_;
}

bool SleepTimer::IsActive() const {
    return is_active_;
}