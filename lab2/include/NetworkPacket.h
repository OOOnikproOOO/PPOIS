/**
 * @file NetworkPacket.h
 * @brief Declaration of the NetworkPacket class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef NETWORKPACKET_H
#define NETWORKPACKET_H

#include <iostream>
#include <string>

/**
 * @brief Represents an IP network packet transmitted across network adapters.
 */
class NetworkPacket {
public:
    /**
     * @brief Constructs a NetworkPacket instance.
     * @param source_ip Originating IPv4/IPv6 address.
     * @param dest_ip Destination IPv4/IPv6 address.
     * @param port Target network port.
     * @param payload_bytes Packet payload size in bytes.
     * @param protocol Transport protocol ("TCP" or "UDP").
     */
    explicit NetworkPacket(const std::string& source_ip = "192.168.1.100", const std::string& dest_ip = "8.8.8.8", int port = 443, int payload_bytes = 64, const std::string& protocol = "TCP");

    /**
     * @brief Equality operator comparing packet headers and payloads.
     * @param other Another NetworkPacket instance.
     * @return true if all packet attributes match.
     */
    bool operator==(const NetworkPacket& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another NetworkPacket instance.
     * @return true if packet attributes differ.
     */
    bool operator!=(const NetworkPacket& other) const;

    /**
     * @brief Stream output operator for formatting packet summary.
     * @param os Output stream.
     * @param packet NetworkPacket instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const NetworkPacket& packet);

    /**
     * @brief Resizes payload bytes and checks non-negative bounds.
     * @param new_size_bytes Target payload byte size.
     */
    void ResizePayload(int new_size_bytes);

    /**
     * @brief Checks if packet is destined for standard encrypted ports (HTTPS 443, SSH 22, IMAPS 993).
     * @return true if port is a secure transport standard.
     */
    bool IsSecurePort() const;

    /**
     * @brief Gets source IP address.
     * @return Source IP string.
     */
    const std::string& GetSourceIp() const;

    /**
     * @brief Gets destination IP address.
     * @return Destination IP string.
     */
    const std::string& GetDestIp() const;

    /**
     * @brief Gets target network port number.
     * @return Port number.
     */
    int GetPort() const;

    /**
     * @brief Gets packet payload size in bytes.
     * @return Payload size in bytes.
     */
    int GetPayloadBytes() const;

    /**
     * @brief Gets transport protocol string.
     * @return Protocol string ("TCP" or "UDP").
     */
    const std::string& GetProtocol() const;

private:
    std::string source_ip_;
    std::string dest_ip_;
    int port_;
    int payload_bytes_;
    std::string protocol_;
};

#endif