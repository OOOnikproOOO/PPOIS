/**
 * @file VideoPort.h
 * @brief Declaration of the VideoPort class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef VIDEOPORT_H
#define VIDEOPORT_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling an individual video display interface port.
 */
class VideoPort {
public:
    /**
     * @brief Constructs a video port with standard resolution limits.
     * @param port_type Interface protocol standard ("DisplayPort 1.4", "HDMI 2.1").
     * @param max_resolution_width Maximum supported width in pixels.
     * @param max_refresh_rate_hz Maximum supported refresh rate in Hz.
     */
    explicit VideoPort(const std::string& port_type = "DisplayPort 1.4", int max_resolution_width = 3840, int max_refresh_rate_hz = 144);

    /**
     * @brief Equality operator comparing port standard and limits.
     * @param other Port to compare with.
     * @return true if properties match.
     */
    bool operator==(const VideoPort& other) const;

    /**
     * @brief Inequality operator.
     * @param other Port to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const VideoPort& other) const;

    /**
     * @brief Stream output operator for formatting port status.
     * @param os Output stream.
     * @param port Port instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const VideoPort& port);

    /**
     * @brief Connects a display cable to this interface.
     */
    void ConnectCable();

    /**
     * @brief Disconnects any active display cable from this interface.
     */
    void DisconnectCable();

    /**
     * @brief Verifies whether this port can transmit the specified display resolution and refresh rate.
     * @param width Target resolution width.
     * @param refresh_rate_hz Target refresh rate in Hz.
     * @return true if target mode is supported.
     */
    bool SupportsDisplayMode(int width, int refresh_rate_hz) const;

    /**
     * @brief Gets port connector protocol type string.
     * @return Port type name.
     */
    std::string GetPortType() const;

    /**
     * @brief Gets maximum supported horizontal resolution width.
     * @return Max width in pixels.
     */
    int GetMaxResolutionWidth() const;

    /**
     * @brief Gets maximum supported refresh rate in Hz.
     * @return Max refresh rate.
     */
    int GetMaxRefreshRateHz() const;

    /**
     * @brief Checks if a cable is currently plugged in.
     * @return true if connected.
     */
    bool IsConnected() const;

private:
    std::string port_type_;
    int max_resolution_width_;
    int max_refresh_rate_hz_;
    bool is_connected_;
};

#endif