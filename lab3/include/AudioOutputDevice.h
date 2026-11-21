/**
 * @file AudioOutputDevice.h
 * @brief Declaration of the AudioOutputDevice class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOOUTPUTDEVICE_H
#define AUDIOOUTPUTDEVICE_H

#include <iostream>
#include <string>

/**
 * @brief Represents a physical or virtual sound rendering destination device (Speakers, Headphones, DAC).
 */
class AudioOutputDevice {
public:
    /**
     * @brief Constructs an AudioOutputDevice.
     * @param device_name Commercial device label.
     * @param device_id Unique hardware GUID string.
     * @param channels_count Channel topology (2 for stereo, 6 for 5.1).
     * @param is_connected Device plugged in status.
     * @param is_default Primary default endpoint flag.
     */
    AudioOutputDevice(const std::string& device_name = "Realtek High Definition Audio", const std::string& device_id = "DEV_001", int channels_count = 2, bool is_connected = true, bool is_default = false);

    /**
     * @brief Compares two AudioOutputDevice instances for equality.
     * @param other Device to compare with.
     * @return true if hardware ID matches.
     */
    bool operator==(const AudioOutputDevice& other) const;

    /**
     * @brief Compares two AudioOutputDevice instances for inequality.
     * @param other Device to compare with.
     * @return true if hardware ID differs.
     */
    bool operator!=(const AudioOutputDevice& other) const;

    /**
     * @brief Stream output operator for formatting AudioOutputDevice info.
     * @param os Output stream.
     * @param dev Device instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioOutputDevice& dev);

    /**
     * @brief Connects audio device endpoint.
     */
    void Connect();

    /**
     * @brief Disconnects audio device endpoint.
     */
    void Disconnect();

    /**
     * @brief Toggles default system output device designation.
     * @param def Default status.
     */
    void SetDefault(bool def);

    /**
     * @brief Formats device descriptor line.
     * @return Formatted device string.
     */
    std::string FormatDeviceInfo() const;

    /**
     * @brief Gets friendly device display name.
     * @return Reference to name string.
     */
    const std::string& GetDeviceName() const;

    /**
     * @brief Gets hardware identifier string.
     * @return Reference to ID string.
     */
    const std::string& GetDeviceId() const;

    /**
     * @brief Gets supported channel count.
     * @return Channel count integer.
     */
    int GetChannelsCount() const;

    /**
     * @brief Checks if device is plugged in and accessible.
     * @return true if connected.
     */
    bool IsConnected() const;

    /**
     * @brief Checks if device is marked as default audio endpoint.
     * @return true if default.
     */
    bool IsDefault() const;

private:
    std::string device_name_;
    std::string device_id_;
    int channels_count_;
    bool is_connected_;
    bool is_default_;
};

#endif