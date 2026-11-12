/**
 * @file DeviceDriver.h
 * @brief Declaration of the DeviceDriver class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#include <iostream>
#include <string>

/**
 * @brief Represents an operating system kernel driver interfacing with hardware components.
 */
class DeviceDriver {
public:
    /**
     * @brief Constructs a DeviceDriver instance.
     * @param driver_name Driver module name.
     * @param version Driver version string.
     * @param device_type Target device category (e.g., "GPU", "Audio", "NVMe").
     * @param is_loaded Whether the driver is loaded into the kernel.
     */
    explicit DeviceDriver(const std::string& driver_name = "nvidia-drm", const std::string& version = "550.54", const std::string& device_type = "GPU", bool is_loaded = false);

    /**
     * @brief Equality operator comparing driver metadata and load state.
     * @param other Another DeviceDriver instance.
     * @return true if drivers match.
     */
    bool operator==(const DeviceDriver& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another DeviceDriver instance.
     * @return true if drivers differ.
     */
    bool operator!=(const DeviceDriver& other) const;

    /**
     * @brief Stream output operator for formatting driver information.
     * @param os Output stream.
     * @param driver DeviceDriver instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const DeviceDriver& driver);

    /**
     * @brief Loads the driver into the operating system kernel.
     */
    void Load();

    /**
     * @brief Unloads the driver from the operating system kernel.
     */
    void Unload();

    /**
     * @brief Updates the driver version string.
     * @param new_version New version string.
     */
    void UpdateVersion(const std::string& new_version);

    /**
     * @brief Gets the driver module name.
     * @return Driver name string.
     */
    const std::string& GetDriverName() const;

    /**
     * @brief Gets the driver version string.
     * @return Version string.
     */
    const std::string& GetVersion() const;

    /**
     * @brief Gets the target hardware device category.
     * @return Device type string.
     */
    const std::string& GetDeviceType() const;

    /**
     * @brief Checks whether the driver is currently loaded.
     * @return true if loaded.
     */
    bool IsLoaded() const;

private:
    std::string driver_name_;
    std::string version_;
    std::string device_type_;
    bool is_loaded_;
};

#endif