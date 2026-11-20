/**
 * @file SleepTimer.h
 * @brief Declaration of the SleepTimer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SLEEPTIMER_H
#define SLEEPTIMER_H

#include <iostream>

/**
 * @brief Automatically halts playback after a programmed duration with optional gradual volume fade-out.
 */
class SleepTimer {
public:
    /**
     * @brief Constructs a SleepTimer.
     * @param duration_minutes Sleep timer countdown duration in minutes.
     * @param fadeout_duration_sec Seconds for soft volume fadeout before stop.
     * @param should_fadeout Gradual volume decrease toggle.
     * @param is_active Timer active state.
     */
    SleepTimer(int duration_minutes = 30, int fadeout_duration_sec = 15, bool should_fadeout = true, bool is_active = false);

    /**
     * @brief Compares two SleepTimer instances for equality.
     * @param other Timer to compare with.
     * @return true if properties match.
     */
    bool operator==(const SleepTimer& other) const;

    /**
     * @brief Compares two SleepTimer instances for inequality.
     * @param other Timer to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const SleepTimer& other) const;

    /**
     * @brief Stream output operator for formatting SleepTimer info.
     * @param os Output stream.
     * @param timer Timer instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SleepTimer& timer);

    /**
     * @brief Starts sleep timer countdown with specified minutes.
     * @param minutes Countdown in minutes.
     * @param fadeout Whether to fade out sound gently.
     */
    void Start(int minutes, bool fadeout = true);

    /**
     * @brief Steps elapsed time and reduces remaining countdown.
     * @param elapsed_minutes Minutes passed.
     */
    void TickMinutes(int elapsed_minutes);

    /**
     * @brief Cancels and disarms active sleep timer.
     */
    void Cancel();

    /**
     * @brief Checks if sleep timer has reached zero.
     * @return true if expired.
     */
    bool IsExpired() const;

    /**
     * @brief Gets remaining countdown minutes.
     * @return Minutes remaining.
     */
    int GetRemainingMinutes() const;

    /**
     * @brief Gets fadeout transition window in seconds.
     * @return Fadeout seconds.
     */
    int GetFadeoutDurationSec() const;

    /**
     * @brief Checks if gentle fadeout is enabled.
     * @return true if fadeout is active.
     */
    bool ShouldFadeout() const;

    /**
     * @brief Checks if timer is currently running.
     * @return true if running.
     */
    bool IsActive() const;

private:
    int duration_minutes_;
    int remaining_minutes_;
    int fadeout_duration_sec_;
    bool should_fadeout_;
    bool is_active_;
};

#endif