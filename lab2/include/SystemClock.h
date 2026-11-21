/**
 * @file SystemClock.h
 * @brief Declaration of the SystemClock class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H

#include <iostream>
#include <string>

/**
 * @brief Represents the system real-time clock (RTC) and OS uptime counter.
 */
class SystemClock {
public:
    /**
     * @brief Constructs a SystemClock instance.
     * @param uptime_seconds Initial uptime in seconds.
     * @param timezone_offset_hours UTC offset in hours (-12 to +14).
     * @param is_ntp_synced Whether time is synchronized via NTP.
     */
    explicit SystemClock(long long uptime_seconds = 0, int timezone_offset_hours = 3, bool is_ntp_synced = true);

    /**
     * @brief Equality operator comparing clock state.
     * @param other Another SystemClock instance.
     * @return true if all fields match.
     */
    bool operator==(const SystemClock& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another SystemClock instance.
     * @return true if clock states differ.
     */
    bool operator!=(const SystemClock& other) const;

    /**
     * @brief Stream output operator for formatting system clock state.
     * @param os Output stream.
     * @param clock SystemClock instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SystemClock& clock);

    /**
     * @brief Advances system uptime by specified seconds.
     * @param seconds Elapsed seconds (>= 0).
     */
    void Tick(long long seconds);

    /**
     * @brief Updates the configured UTC timezone offset.
     * @param offset_hours Offset in hours (-12 to +14).
     */
    void SetTimezoneOffset(int offset_hours);

    /**
     * @brief Synchronizes system clock with network time protocol (NTP).
     */
    void SyncWithNtp();

    /**
     * @brief Formats current uptime as HH:MM:SS string.
     * @return Formatted uptime string.
     */
    std::string FormatUptime() const;

    /**
     * @brief Gets total accumulated system uptime in seconds.
     * @return Uptime in seconds.
     */
    long long GetUptimeSeconds() const;

    /**
     * @brief Gets configured UTC timezone offset in hours.
     * @return Timezone offset in hours.
     */
    int GetTimezoneOffsetHours() const;

    /**
     * @brief Checks whether clock is NTP-synchronized.
     * @return true if synchronized.
     */
    bool IsNtpSynced() const;

private:
    long long uptime_seconds_;
    int timezone_offset_hours_;
    bool is_ntp_synced_;
};

#endif