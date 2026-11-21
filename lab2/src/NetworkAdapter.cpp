/**
 * @file NetworkAdapter.cpp
 * @brief Implementation of NetworkAdapter methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "NetworkAdapter.h"
#include "ComputerException.h"

NetworkAdapter::NetworkAdapter(const std::string& mac_address, const std::string& ip_address, int link_speed_mbps, bool is_connected) :
    mac_address_(mac_address), ip_address_(ip_address), link_speed_mbps_(link_speed_mbps), bytes_sent_(0), bytes_received_(0), is_connected_(is_connected) {}

bool NetworkAdapter::operator==(const NetworkAdapter& other) const {
    return mac_address_ == other.mac_address_ && ip_address_ == other.ip_address_ &&
           link_speed_mbps_ == other.link_speed_mbps_ && bytes_sent_ == other.bytes_sent_ &&
           bytes_received_ == other.bytes_received_ && is_connected_ == other.is_connected_;
}

bool NetworkAdapter::operator!=(const NetworkAdapter& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const NetworkAdapter& adapter) {
    os << "NIC [" << adapter.mac_address_ << ", IP: " << adapter.ip_address_ << ", " << adapter.link_speed_mbps_ << " Mbps, " << (adapter.is_connected_ ? "Connected" : "Disconnected") << ", Tx: " << adapter.bytes_sent_ << " B, Rx: " << adapter.bytes_received_ << " B]";
    return os;
}

void NetworkAdapter::SendPacket(const NetworkPacket& packet) {
    if (!is_connected_) 
        throw ComputerException("Cannot transmit packet: Network adapter link is down.");
    bytes_sent_ += packet.GetPayloadBytes();
}

void NetworkAdapter::ReceivePacket(const NetworkPacket& packet) {
    if (!is_connected_) 
        throw ComputerException("Cannot receive packet: Network adapter link is down.");
    bytes_received_ += packet.GetPayloadBytes();
}

void NetworkAdapter::Connect() {
    is_connected_ = true;
}

void NetworkAdapter::Disconnect() {
    is_connected_ = false;
}

const std::string& NetworkAdapter::GetMacAddress() const {
    return mac_address_;
}

const std::string& NetworkAdapter::GetIpAddress() const {
    return ip_address_;
}

int NetworkAdapter::GetLinkSpeedMbps() const {
    return link_speed_mbps_;
}

long long NetworkAdapter::GetBytesSent() const {
    return bytes_sent_;
}

long long NetworkAdapter::GetBytesReceived() const {
    return bytes_received_;
}

bool NetworkAdapter::IsConnected() const {
    return is_connected_;
}