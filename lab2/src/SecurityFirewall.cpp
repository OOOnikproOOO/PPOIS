/**
 * @file SecurityFirewall.cpp
 * @brief Implementation of SecurityFirewall methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SecurityFirewall.h"
#include "ComputerException.h"

SecurityFirewall::SecurityFirewall(bool is_enabled, const std::string& security_level, int blocked_packets_count) :
    is_enabled_(is_enabled),
    security_level_(security_level),
    blocked_packets_count_(blocked_packets_count),
    allowed_ports_({80, 443, 22, 53}) {}

bool SecurityFirewall::operator==(const SecurityFirewall& other) const {
    return is_enabled_ == other.is_enabled_ && security_level_ == other.security_level_ &&
           blocked_packets_count_ == other.blocked_packets_count_ && allowed_ports_ == other.allowed_ports_;
}

bool SecurityFirewall::operator!=(const SecurityFirewall& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SecurityFirewall& firewall) {
    os << "Firewall [" << (firewall.is_enabled_ ? "ACTIVE" : "DISABLED") << ", Level: " << firewall.security_level_ << ", Blocked: " << firewall.blocked_packets_count_ << " packets, Allowed Ports: " << firewall.allowed_ports_.size() << "]";
    return os;
}

bool SecurityFirewall::InspectPacket(const NetworkPacket& packet) {
    if (!is_enabled_) 
        return true;
    if (!IsPortAllowed(packet.GetPort())) {
        blocked_packets_count_++;
        throw ComputerException("Firewall blocked unauthorized packet to port " + std::to_string(packet.GetPort()) + ".");
    }
    return true;
}

void SecurityFirewall::AllowPort(int port) {
    if (port <= 0 || port > 65535) 
        throw ComputerException("Invalid port number. Must be between 1 and 65535.");
    for (int i = 0; i < static_cast<int>(allowed_ports_.size()); i++) {
        if (allowed_ports_[i] == port) 
            return;
    }
    allowed_ports_.push_back(port);
}

void SecurityFirewall::RevokePort(int port) {
    for (int i = 0; i < static_cast<int>(allowed_ports_.size()); i++) {
        if (allowed_ports_[i] == port) {
            allowed_ports_.erase(allowed_ports_.begin() + i);
            return;
        }
    }
}

void SecurityFirewall::ToggleFirewall(bool enabled) {
    is_enabled_ = enabled;
}

bool SecurityFirewall::IsEnabled() const {
    return is_enabled_;
}

const std::string& SecurityFirewall::GetSecurityLevel() const {
    return security_level_;
}

int SecurityFirewall::GetBlockedPacketsCount() const {
    return blocked_packets_count_;
}

int SecurityFirewall::GetAllowedPortCount() const {
    return static_cast<int>(allowed_ports_.size());
}

bool SecurityFirewall::IsPortAllowed(int port) const {
    for (int i = 0; i < static_cast<int>(allowed_ports_.size()); i++) {
        if (allowed_ports_[i] == port) 
            return true;
    }
    return false;
}