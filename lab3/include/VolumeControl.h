/**
 * @file VolumeControl.h
 * @brief Declaration of the VolumeControl class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef VOLUMECONTROL_H
#define VOLUMECONTROL_H

#include <iostream>
#include <string>

/**
 * @brief Controls output loudness, logarithmic decibel scaling and mute state.
 */
class VolumeControl {
public:
    /**
     * @brief Constructs a VolumeControl.
     * @param volume_level Initial volume percentage (0 to 100).
     * @param is_muted Initial mute toggle.
     * @param max_limit Safe hearing volume ceiling percentage.
     */
    VolumeControl(int volume_level = 70, bool is_muted = false, int max_limit = 100);

    /**
     * @brief Compares two VolumeControl instances for equality.
     * @param other VolumeControl to compare with.
     * @return true if levels and states match.
     */
    bool operator==(const VolumeControl& other) const;

    /**
     * @brief Compares two VolumeControl instances for inequality.
     * @param other VolumeControl to compare with.
     * @return true if levels or states differ.
     */
    bool operator!=(const VolumeControl& other) const;

    /**
     * @brief Stream output operator for formatting VolumeControl info.
     * @param os Output stream.
     * @param vc VolumeControl instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const VolumeControl& vc);

    /**
     * @brief Changes master volume level.
     * @param level Percentage level (0 to 100).
     */
    void SetVolume(int level);

    /**
     * @brief Toggles mute state, restoring previously remembered volume when unmuted.
     */
    void ToggleMute();

    /**
     * @brief Calculates logarithmic gain in decibels.
     * @return Decibels (e.g. 0 dB at 100%, -60 dB at 0%).
     */
    double CalculateGainDecibels() const;

    /**
     * @brief Sets hearing protection upper volume limit.
     * @param limit Maximum allowed percentage.
     */
    void SetMaxLimit(int limit);

    /**
     * @brief Resets volume to 50% unmuted.
     */
    void Reset();

    /**
     * @brief Gets current set volume level percentage.
     * @return Volume percentage (0 to 100).
     */
    int GetVolumeLevel() const;

    /**
     * @brief Checks if audio output is muted.
     * @return true if muted.
     */
    bool IsMuted() const;

    /**
     * @brief Gets safety hearing limit percentage.
     * @return Limit percentage.
     */
    int GetMaxLimit() const;

    /**
     * @brief Gets effective audible volume level (0 if muted).
     * @return Audible volume percentage.
     */
    int GetEffectiveVolume() const;

private:
    int volume_level_;
    bool is_muted_;
    int saved_volume_;
    int max_limit_;
};

#endif