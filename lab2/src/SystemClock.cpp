/**
 * @file SystemClock.cpp
 * @brief Implementation of SystemClock methods.
 * @author Nikita Momot
 * @date 2026
 */

#include <iomanip>
#include <sstream>
#include "SystemClock.h"
#include "ComputerException.h"

SystemClock::SystemClock(long long uptime_seconds, int timezone_offset_hours, bool is_ntp_synced) :
    uptime_seconds_(uptime_seconds), timezone_offset_hours_(timezone_offset_hours), is_ntp_synced_(is_ntp_synced) {}

bool SystemClock::operator==(const SystemClock& other) const {
    return uptime_seconds_ == other.uptime_seconds_ && timezone_offset_hours_ == other.timezone_offset_hours_ && is_ntp_synced_ == other.is_ntp_synced_;
}

bool SystemClock::operator!=(const SystemClock& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SystemClock& clock) {
    os << "SystemClock [Uptime: " << clock.FormatUptime() << ", UTC" << (clock.timezone_offset_hours_ >= 0 ? "+" : "") << clock.timezone_offset_hours_ << ", NTP: " << (clock.is_ntp_synced_ ? "Synced" : "Unsynced") << "]";
    return os;
}

void SystemClock::Tick(long long seconds) {
    if (seconds < 0) 
        throw ComputerException("Clock tick duration cannot be negative.");
    uptime_seconds_ += seconds;
}

void SystemClock::SetTimezoneOffset(int offset_hours) {
    if (offset_hours < -12 || offset_hours > 14) 
        throw ComputerException("Timezone offset must be between -12 and +14 hours.");
    timezone_offset_hours_ = offset_hours;
}

void SystemClock::SyncWithNtp() {
    is_ntp_synced_ = true;
}

std::string SystemClock::FormatUptime() const {
    long long hours = uptime_seconds_ / 3600;
    long long minutes = (uptime_seconds_ % 3600) / 60;
    long long seconds = uptime_seconds_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
    return oss.str();
}

long long SystemClock::GetUptimeSeconds() const {
    return uptime_seconds_;
}

int SystemClock::GetTimezoneOffsetHours() const {
    return timezone_offset_hours_;
}

bool SystemClock::IsNtpSynced() const {
    return is_ntp_synced_;
}