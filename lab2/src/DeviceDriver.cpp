/**
 * @file DeviceDriver.cpp
 * @brief Implementation of DeviceDriver methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "DeviceDriver.h"
#include "ComputerException.h"

DeviceDriver::DeviceDriver(const std::string& driver_name, const std::string& version, const std::string& device_type, bool is_loaded) :
    driver_name_(driver_name), version_(version), device_type_(device_type), is_loaded_(is_loaded) {}

bool DeviceDriver::operator==(const DeviceDriver& other) const {
    return driver_name_ == other.driver_name_ && version_ == other.version_ &&
           device_type_ == other.device_type_ && is_loaded_ == other.is_loaded_;
}

bool DeviceDriver::operator!=(const DeviceDriver& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const DeviceDriver& driver) {
    os << "Driver '" << driver.driver_name_ << "' v" << driver.version_ << " [" << driver.device_type_ << ", " << (driver.is_loaded_ ? "Loaded" : "Unloaded") << "]";
    return os;
}

void DeviceDriver::Load() {
    is_loaded_ = true;
}

void DeviceDriver::Unload() {
    is_loaded_ = false;
}

void DeviceDriver::UpdateVersion(const std::string& new_version) {
    if (new_version.empty()) 
        throw ComputerException("Driver version string cannot be empty.");
    version_ = new_version;
}

const std::string& DeviceDriver::GetDriverName() const {
    return driver_name_;
}

const std::string& DeviceDriver::GetVersion() const {
    return version_;
}

const std::string& DeviceDriver::GetDeviceType() const {
    return device_type_;
}

bool DeviceDriver::IsLoaded() const {
    return is_loaded_;
}