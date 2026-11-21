/**
 * @file CrossfadeEngine.h
 * @brief Declaration of the CrossfadeEngine class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef CROSSFADEENGINE_H
#define CROSSFADEENGINE_H

#include <iostream>
#include <string>

/**
 * @brief Computes dynamic volume mix coefficients for gapless crossfade between successive tracks.
 */
class CrossfadeEngine {
public:
    /**
     * @brief Constructs a CrossfadeEngine.
     * @param duration_sec Crossfade transition time in seconds.
     * @param is_enabled Enable crossfading flag.
     * @param transition_curve Curve shape ("Linear", "Exponential", "EqualPower").
     */
    CrossfadeEngine(double duration_sec = 4.0, bool is_enabled = true, const std::string& transition_curve = "EqualPower");

    /**
     * @brief Compares two CrossfadeEngine instances for equality.
     * @param other Engine to compare with.
     * @return true if parameters match.
     */
    bool operator==(const CrossfadeEngine& other) const;

    /**
     * @brief Compares two CrossfadeEngine instances for inequality.
     * @param other Engine to compare with.
     * @return true if parameters differ.
     */
    bool operator!=(const CrossfadeEngine& other) const;

    /**
     * @brief Stream output operator for formatting CrossfadeEngine info.
     * @param os Output stream.
     * @param engine Engine instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const CrossfadeEngine& engine);

    /**
     * @brief Computes instantaneous fade-out and fade-in gain multipliers.
     * @param current_crossfade_time Elapsed time inside crossfade window.
     * @param out_track1_vol Calculated gain for outgoing track (0.0 to 1.0).
     * @param out_track2_vol Calculated gain for incoming track (0.0 to 1.0).
     */
    void CalculateMixCoefficients(double current_crossfade_time, double& out_track1_vol, double& out_track2_vol) const;

    /**
     * @brief Sets crossfade transition window in seconds.
     * @param sec Duration seconds (0.5 to 15.0).
     */
    void SetDuration(double sec);

    /**
     * @brief Toggles crossfade processing.
     * @param enable Flag.
     */
    void ToggleCrossfade(bool enable);

    /**
     * @brief Sets fade curve equation.
     * @param curve Curve name.
     */
    void SetCurve(const std::string& curve);

    /**
     * @brief Gets crossfade transition duration in seconds.
     * @return Duration in seconds.
     */
    double GetDurationSec() const;

    /**
     * @brief Checks if crossfading is enabled.
     * @return true if enabled.
     */
    bool IsEnabled() const;

    /**
     * @brief Gets active transition curve profile name.
     * @return Reference to curve string.
     */
    const std::string& GetTransitionCurve() const;

private:
    double duration_sec_;
    bool is_enabled_;
    std::string transition_curve_;
};

#endif