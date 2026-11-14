/**
 * @file NetworkPacket.cpp
 * @brief Implementation of NetworkPacket methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "NetworkPacket.h"
#include "ComputerException.h"

NetworkPacket::NetworkPacket(const std::string& source_ip, const std::string& dest_ip, int port, int payload_bytes, const std::string& protocol) :
    source_ip_(source_ip), dest_ip_(dest_ip), port_(port), payload_bytes_(payload_bytes), protocol_(protocol) {}

bool NetworkPacket::operator==(const NetworkPacket& other) const {
    return source_ip_ == other.source_ip_ && dest_ip_ == other.dest_ip_ &&
           port_ == other.port_ && payload_bytes_ == other.payload_bytes_ &&
           protocol_ == other.protocol_;
}

bool NetworkPacket::operator!=(const NetworkPacket& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const NetworkPacket& packet) {
    os << "Packet [" << packet.protocol_ << " " << packet.source_ip_ << " -> " << packet.dest_ip_ << ":" << packet.port_ << " (" << packet.payload_bytes_ << " B)]";
    return os;
}

void NetworkPacket::ResizePayload(int new_size_bytes) {
    if (new_size_bytes < 0) 
        throw ComputerException("Packet payload size cannot be negative.");
    payload_bytes_ = new_size_bytes;
}

bool NetworkPacket::IsSecurePort() const {
    return port_ == 443 || port_ == 22 || port_ == 993 || port_ == 8443;
}

const std::string& NetworkPacket::GetSourceIp() const {
    return source_ip_;
}

const std::string& NetworkPacket::GetDestIp() const {
    return dest_ip_;
}

int NetworkPacket::GetPort() const {
    return port_;
}

int NetworkPacket::GetPayloadBytes() const {
    return payload_bytes_;
}

const std::string& NetworkPacket::GetProtocol() const {
    return protocol_;
}