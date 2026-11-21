/**
 * @file DeviceManager.h
 * @brief Declaration of the DeviceManager class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "AudioOutputDevice.h"

/**
 * @brief Manages audio hardware output device enumeration, hotplugging and default audio route selection.
 */
class DeviceManager {
public:
    /**
     * @brief Constructs a DeviceManager.
     * @param auto_switch_on_connect Automatically route audio to newly plugged devices.
     */
    explicit DeviceManager(bool auto_switch_on_connect = true);

    /**
     * @brief Compares two DeviceManager instances for equality.
     * @param other Manager to compare with.
     * @return true if devices and active selection match.
     */
    bool operator==(const DeviceManager& other) const;

    /**
     * @brief Compares two DeviceManager instances for inequality.
     * @param other Manager to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const DeviceManager& other) const;

    /**
     * @brief Stream output operator for formatting DeviceManager info.
     * @param os Output stream.
     * @param dm DeviceManager instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const DeviceManager& dm);

    /**
     * @brief Registers an audio output device.
     * @param device AudioOutputDevice to add.
     */
    void RegisterDevice(const AudioOutputDevice& device);

    /**
     * @brief Selects active device by hardware ID.
     * @param device_id Unique ID of device.
     * @throws DeviceAudioOutputException if device is not found or is disconnected.
     */
    void SelectActiveDevice(const std::string& device_id);

    /**
     * @brief Unregisters a device by hardware ID.
     * @param device_id Hardware ID.
     */
    void RemoveDevice(const std::string& device_id);

    /**
     * @brief Returns active output device.
     * @return Const reference to active AudioOutputDevice.
     * @throws DeviceAudioOutputException if no active device is available.
     */
    const AudioOutputDevice& GetActiveDevice() const;

    /**
     * @brief Clears all registered devices.
     */
    void Clear();

    /**
     * @brief Gets count of registered audio devices.
     * @return Device count.
     */
    size_t GetDevicesCount() const;

    /**
     * @brief Checks if auto-switching on connect is enabled.
     * @return true if auto-switch is on.
     */
    bool IsAutoSwitchOnConnect() const;

    /**
     * @brief Gets index of active output device.
     * @return Device index or -1 if none.
     */
    int GetActiveDeviceIndex() const;

    /**
     * @brief Gets constant reference to all registered output devices.
     * @return Reference to vector of AudioOutputDevice.
     */
    const std::vector<AudioOutputDevice>& GetDevices() const;

private:
    bool auto_switch_on_connect_;
    int active_device_index_;
    std::vector<AudioOutputDevice> devices_;
};

#endif