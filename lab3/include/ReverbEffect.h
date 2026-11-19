/**
 * @file ReverbEffect.h
 * @brief Declaration of the ReverbEffect class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef REVERBEFFECT_H
#define REVERBEFFECT_H

#include <iostream>

/**
 * @brief Spatial reverberation audio effect simulating acoustic reflections in physical rooms.
 */
class ReverbEffect {
public:
    /**
     * @brief Constructs a ReverbEffect.
     * @param room_size Virtual room volume (0.0 to 1.0).
     * @param damping High-frequency absorption (0.0 to 1.0).
     * @param wet_level Wet/dry wetness ratio (0.0 to 1.0).
     * @param is_active Effect enabled flag.
     */
    ReverbEffect(double room_size = 0.5, double damping = 0.3, double wet_level = 0.25, bool is_active = false);

    /**
     * @brief Compares two ReverbEffect instances for equality.
     * @param other Effect to compare with.
     * @return true if parameters match.
     */
    bool operator==(const ReverbEffect& other) const;

    /**
     * @brief Compares two ReverbEffect instances for inequality.
     * @param other Effect to compare with.
     * @return true if parameters differ.
     */
    bool operator!=(const ReverbEffect& other) const;

    /**
     * @brief Stream output operator for formatting ReverbEffect info.
     * @param os Output stream.
     * @param effect Effect instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ReverbEffect& effect);

    /**
     * @brief Processes an audio sample through reverberation reflections.
     * @param input_amplitude Incoming signal.
     * @return Reverberated output signal.
     */
    double ProcessSample(double input_amplitude) const;

    /**
     * @brief Adjusts room size simulation.
     * @param size Normalized size (0.0 to 1.0).
     */
    void SetRoomSize(double size);

    /**
     * @brief Sets absorption factor.
     * @param damp Damping coefficient (0.0 to 1.0).
     */
    void SetDamping(double damp);

    /**
     * @brief Sets wet mix balance.
     * @param wet Wet fraction (0.0 to 1.0).
     */
    void SetWetLevel(double wet);

    /**
     * @brief Toggles reverb processing.
     * @param active State.
     */
    void ToggleEffect(bool active);

    /**
     * @brief Gets virtual room size parameter.
     * @return Size value (0.0 to 1.0).
     */
    double GetRoomSize() const;

    /**
     * @brief Gets high-frequency absorption damping.
     * @return Damping coefficient (0.0 to 1.0).
     */
    double GetDamping() const;

    /**
     * @brief Gets wet mix level fraction.
     * @return Wet level (0.0 to 1.0).
     */
    double GetWetLevel() const;

    /**
     * @brief Checks if reverb processing is active.
     * @return true if active.
     */
    bool IsActive() const;

private:
    double room_size_;
    double damping_;
    double wet_level_;
    bool is_active_;
};

#endif