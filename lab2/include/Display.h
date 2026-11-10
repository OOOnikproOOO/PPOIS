/**
 * @file Display.h
 * @brief Declaration of the Display class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling an external computer display monitor.
 */
class Display {
public:
    /**
     * @brief Constructs a display monitor with standard screen parameters.
     * @param model Commercial monitor model name.
     * @param resolution_width Horizontal pixel resolution.
     * @param resolution_height Vertical pixel resolution.
     * @param refresh_rate_hz Panel refresh rate in Hz.
     */
    explicit Display(const std::string& model = "LG UltraGear 27GP850", int resolution_width = 2560, int resolution_height = 1440, int refresh_rate_hz = 165);

    /**
     * @brief Compares two displays for equality.
     * @param other Display to compare with.
     * @return true if model and resolution match.
     */
    bool operator==(const Display& other) const;

    /**
     * @brief Inequality operator.
     * @param other Display to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const Display& other) const;

    /**
     * @brief Stream output operator for formatting display status.
     * @param os Output stream.
     * @param display Display instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Display& display);

    /**
     * @brief Toggles the monitor power state between On and Standby.
     */
    void PowerToggle();

    /**
     * @brief Adjusts the operating display resolution.
     * @param width Horizontal resolution in pixels.
     * @param height Vertical resolution in pixels.
     */
    void SetResolution(int width, int height);

    /**
     * @brief Adjusts panel refresh frequency.
     * @param hz Desired refresh rate in Hz.
     */
    void SetRefreshRate(int hz);

    /**
     * @brief Computes total active pixel count on the panel.
     * @return Total pixels (width * height).
     */
    long long CalculateTotalPixels() const;

    /**
     * @brief Gets monitor model name.
     * @return Model string.
     */
    std::string GetModel() const;

    /**
     * @brief Gets horizontal resolution in pixels.
     * @return Width in pixels.
     */
    int GetResolutionWidth() const;

    /**
     * @brief Gets vertical resolution in pixels.
     * @return Height in pixels.
     */
    int GetResolutionHeight() const;

    /**
     * @brief Gets refresh rate in Hz.
     * @return Refresh rate.
     */
    int GetRefreshRateHz() const;

    /**
     * @brief Checks if monitor panel is currently powered on.
     * @return true if powered on.
     */
    bool IsPoweredOn() const;

private:
    std::string model_;
    int resolution_width_;
    int resolution_height_;
    int refresh_rate_hz_;
    bool is_powered_on_;
};

#endif