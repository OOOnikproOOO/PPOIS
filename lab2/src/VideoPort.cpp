/**
 * @file VideoPort.cpp
 * @brief Implementation of VideoPort methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "VideoPort.h"

VideoPort::VideoPort(const std::string& port_type, int max_resolution_width, int max_refresh_rate_hz) :
    port_type_(port_type), max_resolution_width_(max_resolution_width), max_refresh_rate_hz_(max_refresh_rate_hz), is_connected_(false) {}

bool VideoPort::operator==(const VideoPort& other) const {
    return (port_type_ == other.port_type_ &&
            max_resolution_width_ == other.max_resolution_width_ &&
            max_refresh_rate_hz_ == other.max_refresh_rate_hz_ &&
            is_connected_ == other.is_connected_);
}

bool VideoPort::operator!=(const VideoPort& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const VideoPort& port) {
    os << "VideoPort [" << port.port_type_ << ", Max: " << port.max_resolution_width_ << "p@" << port.max_refresh_rate_hz_ << "Hz, " << (port.is_connected_ ? "Connected" : "Disconnected") << "]";
    return os;
}

void VideoPort::ConnectCable() {
    is_connected_ = true;
}

void VideoPort::DisconnectCable() {
    is_connected_ = false;
}

bool VideoPort::SupportsDisplayMode(int width, int refresh_rate_hz) const {
    if (width <= 0 || refresh_rate_hz <= 0)
        return false;
    
    return (width <= max_resolution_width_ && refresh_rate_hz <= max_refresh_rate_hz_);
}

std::string VideoPort::GetPortType() const {
    return port_type_;
}

int VideoPort::GetMaxResolutionWidth() const {
    return max_resolution_width_;
}

int VideoPort::GetMaxRefreshRateHz() const {
    return max_refresh_rate_hz_;
}

bool VideoPort::IsConnected() const {
    return is_connected_;
}