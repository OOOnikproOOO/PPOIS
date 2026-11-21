/**
 * @file SpeakerSystem.h
 * @brief Declaration of the SpeakerSystem class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SPEAKERSYSTEM_H
#define SPEAKERSYSTEM_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling external audio speakers or studio monitors.
 */
class SpeakerSystem {
public:
    /**
     * @brief Constructs an acoustic speaker system.
     * @param system_name Commercial product name.
     * @param power_watts_rms RMS continuous power rating in Watts.
     * @param initial_volume Starting volume level (0 to 100).
     */
    explicit SpeakerSystem(const std::string& system_name = "Edifier R1280DB", int power_watts_rms = 42, int initial_volume = 30);

    /**
     * @brief Compares two speaker systems for equality.
     * @param other SpeakerSystem to compare with.
     * @return true if properties match.
     */
    bool operator==(const SpeakerSystem& other) const;

    /**
     * @brief Inequality operator.
     * @param other SpeakerSystem to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const SpeakerSystem& other) const;

    /**
     * @brief Stream output operator for formatting speaker state.
     * @param os Output stream.
     * @param speaker SpeakerSystem instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SpeakerSystem& speaker);

    /**
     * @brief Adjusts output volume percentage.
     * @param volume Target volume (0 to 100).
     */
    void SetVolume(int volume);

    /**
     * @brief Toggles audio mute state.
     */
    void ToggleMute();

    /**
     * @brief Simulates emitting sound output through acoustic drivers.
     * @param duration_seconds Sound playback length in seconds.
     * @param db_level Decibel pressure output level.
     * @return true if sound was emitted successfully.
     */
    bool OutputSound(int duration_seconds, double db_level);

    /**
     * @brief Gets speaker system model name.
     * @return System name string.
     */
    std::string GetSystemName() const;

    /**
     * @brief Gets RMS continuous power rating in Watts.
     * @return Power rating in Watts.
     */
    int GetPowerWattsRms() const;

    /**
     * @brief Gets current volume percentage.
     * @return Volume (0 to 100).
     */
    int GetCurrentVolume() const;

    /**
     * @brief Checks if audio output is muted.
     * @return true if muted.
     */
    bool IsMuted() const;

private:
    std::string system_name_;
    int power_watts_rms_;
    int current_volume_;
    bool is_muted_;
};

#endif