/**
 * @file USBPort.cpp
 * @brief Implementation of USBPort methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "USBPort.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

USBPort::USBPort(const std::string& port_type, const std::string& protocol_version, bool is_connected, const std::string& connected_device) :
    port_type_(port_type), protocol_version_(protocol_version), is_connected_(is_connected), connected_device_(connected_device) {}

bool USBPort::operator==(const USBPort& other) const {
    return port_type_ == other.port_type_ && protocol_version_ == other.protocol_version_ &&
           is_connected_ == other.is_connected_ && connected_device_ == other.connected_device_;
}

bool USBPort::operator!=(const USBPort& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const USBPort& port) {
    os << "USBPort [" << port.port_type_ << ", " << port.protocol_version_ << ", " << (port.is_connected_ ? "Connected: " + port.connected_device_ : "Empty") << "]";
    return os;
}

void USBPort::ConnectDevice(const std::string& device_name) {
    if (device_name.empty()) 
        throw ComputerException("Connected USB device name cannot be empty.");
    if (is_connected_) 
        throw ComputerException("USB port is already occupied by '" + connected_device_ + "'.");
    is_connected_ = true;
    connected_device_ = device_name;
}

void USBPort::DisconnectDevice() {
    if (!is_connected_) 
        throw DeviceNotFoundException("Cannot disconnect: USB port is already empty.");
    is_connected_ = false;
    connected_device_.clear();
}

double USBPort::CalculateMaxTransferRateMBs() const {
    if (protocol_version_.find("USB4") != std::string::npos) 
        return 5000.0;
    if (protocol_version_.find("3.2") != std::string::npos) 
        return 1250.0;
    if (protocol_version_.find("3.0") != std::string::npos) 
        return 625.0;
    return 60.0;
}

const std::string& USBPort::GetPortType() const {
    return port_type_;
}

const std::string& USBPort::GetProtocolVersion() const {
    return protocol_version_;
}

const std::string& USBPort::GetConnectedDevice() const {
    return connected_device_;
}

bool USBPort::IsConnected() const {
    return is_connected_;
}