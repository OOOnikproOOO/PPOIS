/**
 * @file NetworkAdapter.h
 * @brief Declaration of the NetworkAdapter class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef NETWORKADAPTER_H
#define NETWORKADAPTER_H

#include <iostream>
#include <string>
#include "NetworkPacket.h"

/**
 * @brief Represents a physical network interface controller (NIC) supporting Ethernet and Wi-Fi.
 */
class NetworkAdapter {
public:
    /**
     * @brief Constructs a NetworkAdapter instance.
     * @param mac_address Unique hardware MAC address.
     * @param ip_address Assigned local IP address.
     * @param link_speed_mbps Connection bandwidth in Mbps (e.g. 1000 or 2500).
     * @param is_connected Whether Ethernet cable or Wi-Fi link is active.
     */
    explicit NetworkAdapter(const std::string& mac_address = "00:1A:2B:3C:4D:5E", const std::string& ip_address = "192.168.1.105", int link_speed_mbps = 2500, bool is_connected = true);

    /**
     * @brief Equality operator comparing adapter configurations and metrics.
     * @param other Another NetworkAdapter instance.
     * @return true if adapters match.
     */
    bool operator==(const NetworkAdapter& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another NetworkAdapter instance.
     * @return true if adapters differ.
     */
    bool operator!=(const NetworkAdapter& other) const;

    /**
     * @brief Stream output operator for formatting network adapter status.
     * @param os Output stream.
     * @param adapter NetworkAdapter instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const NetworkAdapter& adapter);

    /**
     * @brief Transmits a network packet and accumulates transmitted bytes.
     * @param packet NetworkPacket to transmit.
     */
    void SendPacket(const NetworkPacket& packet);

    /**
     * @brief Ingests an incoming packet and accumulates received bytes.
     * @param packet Ingested NetworkPacket.
     */
    void ReceivePacket(const NetworkPacket& packet);

    /**
     * @brief Connects the network interface link.
     */
    void Connect();

    /**
     * @brief Disconnects the network interface link.
     */
    void Disconnect();

    /**
     * @brief Gets unique hardware MAC address.
     * @return MAC address string.
     */
    const std::string& GetMacAddress() const;

    /**
     * @brief Gets assigned IPv4 address.
     * @return IP address string.
     */
    const std::string& GetIpAddress() const;

    /**
     * @brief Gets active link speed in Mbps.
     * @return Link speed.
     */
    int GetLinkSpeedMbps() const;

    /**
     * @brief Gets total bytes transmitted.
     * @return Transmitted byte count.
     */
    long long GetBytesSent() const;

    /**
     * @brief Gets total bytes received.
     * @return Received byte count.
     */
    long long GetBytesReceived() const;

    /**
     * @brief Checks whether physical network connection is active.
     * @return true if connected.
     */
    bool IsConnected() const;

private:
    std::string mac_address_;
    std::string ip_address_;
    int link_speed_mbps_;
    long long bytes_sent_;
    long long bytes_received_;
    bool is_connected_;
};

#endif