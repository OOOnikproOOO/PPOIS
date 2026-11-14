/**
 * @file SecurityFirewall.h
 * @brief Declaration of the SecurityFirewall class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SECURITYFIREWALL_H
#define SECURITYFIREWALL_H

#include <iostream>
#include <string>
#include <vector>
#include "NetworkPacket.h"

/**
 * @brief Represents a packet filtering security firewall monitoring inbound and outbound traffic.
 */
class SecurityFirewall {
public:
    /**
     * @brief Constructs a SecurityFirewall instance.
     * @param is_enabled Whether active packet inspection is enabled.
     * @param security_level Defense profile ("Low", "Medium", or "Strict").
     * @param blocked_packets_count Initial count of blocked packets.
     */
    explicit SecurityFirewall(bool is_enabled = true, const std::string& security_level = "Medium", int blocked_packets_count = 0);

    /**
     * @brief Equality operator comparing firewall policies and counters.
     * @param other Another SecurityFirewall instance.
     * @return true if firewall states match.
     */
    bool operator==(const SecurityFirewall& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another SecurityFirewall instance.
     * @return true if firewall states differ.
     */
    bool operator!=(const SecurityFirewall& other) const;

    /**
     * @brief Stream output operator for formatting firewall status.
     * @param os Output stream.
     * @param firewall SecurityFirewall instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SecurityFirewall& firewall);

    /**
     * @brief Inspects a network packet against firewall rules and ports.
     * @param packet Packet to inspect.
     * @return true if packet is approved and forwarded.
     */
    bool InspectPacket(const NetworkPacket& packet);

    /**
     * @brief Adds a network port to the allowed port whitelist.
     * @param port Port number to allow.
     */
    void AllowPort(int port);

    /**
     * @brief Revokes a network port from the allowed whitelist.
     * @param port Port number to revoke.
     */
    void RevokePort(int port);

    /**
     * @brief Toggles firewall inspection activity.
     * @param enabled Target firewall state.
     */
    void ToggleFirewall(bool enabled);

    /**
     * @brief Checks whether the firewall is currently active.
     * @return true if enabled.
     */
    bool IsEnabled() const;

    /**
     * @brief Gets active defense security level string.
     * @return Security level ("Low", "Medium", "Strict").
     */
    const std::string& GetSecurityLevel() const;

    /**
     * @brief Gets total count of unauthorized packets blocked.
     * @return Blocked packet count.
     */
    int GetBlockedPacketsCount() const;

    /**
     * @brief Gets count of whitelisted open ports.
     * @return Whitelisted port count.
     */
    int GetAllowedPortCount() const;

    /**
     * @brief Checks if a specific port is in the whitelist.
     * @param port Port to query.
     * @return true if port is allowed.
     */
    bool IsPortAllowed(int port) const;

private:
    bool is_enabled_;
    std::string security_level_;
    int blocked_packets_count_;
    std::vector<int> allowed_ports_;
};

#endif