/**
 * @file AudioOutputDevice.cpp
 * @brief Implementation of AudioOutputDevice methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioOutputDevice.h"
#include <sstream>

AudioOutputDevice::AudioOutputDevice(const std::string& device_name, const std::string& device_id, int channels_count, bool is_connected, bool is_default) :
    device_name_(device_name), device_id_(device_id), channels_count_(channels_count < 1 ? 1 : (channels_count > 8 ? 8 : channels_count)), is_connected_(is_connected), is_default_(is_default) {}

bool AudioOutputDevice::operator==(const AudioOutputDevice& other) const {
    return device_id_ == other.device_id_;
}

bool AudioOutputDevice::operator!=(const AudioOutputDevice& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioOutputDevice& dev) {
    os << dev.FormatDeviceInfo();
    return os;
}

void AudioOutputDevice::Connect() {
    is_connected_ = true;
}

void AudioOutputDevice::Disconnect() {
    is_connected_ = false;
    is_default_ = false;
}

void AudioOutputDevice::SetDefault(bool def) {
    is_default_ = def;
    if (is_default_)
        is_connected_ = true;
}

std::string AudioOutputDevice::FormatDeviceInfo() const {
    std::ostringstream oss;
    oss << device_name_ << " (ID: " << device_id_ << ", " << channels_count_ << "ch)" << (is_connected_ ? " [Connected]" : " [Disconnected]") << (is_default_ ? " *DEFAULT*" : "");
    return oss.str();
}

const std::string& AudioOutputDevice::GetDeviceName() const {
    return device_name_;
}

const std::string& AudioOutputDevice::GetDeviceId() const {
    return device_id_;
}

int AudioOutputDevice::GetChannelsCount() const {
    return channels_count_;
}

bool AudioOutputDevice::IsConnected() const {
    return is_connected_;
}

bool AudioOutputDevice::IsDefault() const {
    return is_default_;
}