/**
 * @file USBPort.h
 * @brief Declaration of the USBPort class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef USBPORT_H
#define USBPORT_H

#include <iostream>
#include <string>

/**
 * @brief Represents an external Universal Serial Bus (USB) port interfacing with peripherals.
 */
class USBPort {
public:
    /**
     * @brief Constructs a USBPort instance.
     * @param port_type Physical connector type ("Type-A" or "Type-C").
     * @param protocol_version Communication standard (e.g. "USB 3.2 Gen 2").
     * @param is_connected Whether a peripheral cable is plugged in.
     * @param connected_device Name of the currently attached peripheral device.
     */
    explicit USBPort(const std::string& port_type = "Type-C", const std::string& protocol_version = "USB 3.2 Gen 2", bool is_connected = false, const std::string& connected_device = "");

    /**
     * @brief Equality operator comparing USB port states.
     * @param other Another USBPort instance.
     * @return true if USB ports match.
     */
    bool operator==(const USBPort& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another USBPort instance.
     * @return true if USB ports differ.
     */
    bool operator!=(const USBPort& other) const;

    /**
     * @brief Stream output operator for formatting USB port info.
     * @param os Output stream.
     * @param port USBPort instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const USBPort& port);

    /**
     * @brief Plugs a peripheral device into the USB port.
     * @param device_name Name of attached device.
     */
    void ConnectDevice(const std::string& device_name);

    /**
     * @brief Unplugs the device currently connected to the port.
     */
    void DisconnectDevice();

    /**
     * @brief Calculates theoretical maximum transfer rate in MB/s.
     * @return Peak transfer speed in MB/s.
     */
    double CalculateMaxTransferRateMBs() const;

    /**
     * @brief Gets physical connector type.
     * @return Connector string.
     */
    const std::string& GetPortType() const;

    /**
     * @brief Gets protocol specification version.
     * @return Protocol string.
     */
    const std::string& GetProtocolVersion() const;

    /**
     * @brief Gets name of connected peripheral device.
     * @return Device name string.
     */
    const std::string& GetConnectedDevice() const;

    /**
     * @brief Checks whether a device is currently plugged in.
     * @return true if occupied.
     */
    bool IsConnected() const;

private:
    std::string port_type_;
    std::string protocol_version_;
    bool is_connected_;
    std::string connected_device_;
};

#endif