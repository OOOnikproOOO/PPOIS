/**
 * @file DeviceManager.cpp
 * @brief Implementation of DeviceManager methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "DeviceManager.h"
#include "DeviceAudioOutputException.h"

DeviceManager::DeviceManager(bool auto_switch_on_connect) :
    auto_switch_on_connect_(auto_switch_on_connect), active_device_index_(-1) {}

bool DeviceManager::operator==(const DeviceManager& other) const {
    return auto_switch_on_connect_ == other.auto_switch_on_connect_ &&
           active_device_index_ == other.active_device_index_ &&
           devices_ == other.devices_;
}

bool DeviceManager::operator!=(const DeviceManager& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const DeviceManager& dm) {
    os << "DeviceManager[" << dm.devices_.size() << " devices, Active Index: " << dm.active_device_index_ << "]";
    return os;
}

void DeviceManager::RegisterDevice(const AudioOutputDevice& device) {
    devices_.push_back(device);
    if (active_device_index_ == -1 || (auto_switch_on_connect_ && device.IsConnected()))
        active_device_index_ = static_cast<int>(devices_.size()) - 1;
}

void DeviceManager::SelectActiveDevice(const std::string& device_id) {
    for (size_t i = 0; i < devices_.size(); i++) {
        if (devices_[i].GetDeviceId() == device_id) {
            if (!devices_[i].IsConnected())
                throw DeviceAudioOutputException("Cannot select device '" + device_id + "': device is disconnected.");

            active_device_index_ = static_cast<int>(i);
            return;
        }
    }

    throw DeviceAudioOutputException("Audio device with ID '" + device_id + "' was not found.");
}

void DeviceManager::RemoveDevice(const std::string& device_id) {
    for (auto it = devices_.begin(); it != devices_.end(); it++) {
        if (it->GetDeviceId() == device_id) {
            devices_.erase(it);
            if (devices_.empty())
                active_device_index_ = -1;
            else if (active_device_index_ >= static_cast<int>(devices_.size()))
                active_device_index_ = static_cast<int>(devices_.size()) - 1;

            return;
        }
    }
}

const AudioOutputDevice& DeviceManager::GetActiveDevice() const {
    if (active_device_index_ < 0 || active_device_index_ >= static_cast<int>(devices_.size()))
        throw DeviceAudioOutputException("No active audio output device is currently selected.");

    return devices_[active_device_index_];
}

void DeviceManager::Clear() {
    devices_.clear();
    active_device_index_ = -1;
}

size_t DeviceManager::GetDevicesCount() const {
    return devices_.size();
}

bool DeviceManager::IsAutoSwitchOnConnect() const {
    return auto_switch_on_connect_;
}

int DeviceManager::GetActiveDeviceIndex() const {
    return active_device_index_;
}

const std::vector<AudioOutputDevice>& DeviceManager::GetDevices() const {
    return devices_;
}