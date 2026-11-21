/**
 * @file SubscriptionPlan.h
 * @brief Declaration of the SubscriptionPlan class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SUBSCRIPTIONPLAN_H
#define SUBSCRIPTIONPLAN_H

#include <iostream>
#include <string>

/**
 * @brief Manages streaming tier licenses (Free, Premium, HiFi), bitrate ceilings and offline download DRM entitlements.
 */
class SubscriptionPlan {
public:
    /**
     * @brief Constructs a SubscriptionPlan.
     * @param tier_name Plan tier designation ("Free", "Premium", "HiFi").
     * @param max_bitrate_kbps Maximum streaming bitrate authorized.
     * @param allows_offline Offline track caching entitlement.
     * @param expiry_date Subscription expiration date string (YYYY.MM.DD).
     */
    SubscriptionPlan(const std::string& tier_name = "Premium", int max_bitrate_kbps = 320, bool allows_offline = true, const std::string& expiry_date = "2026.12.31");

    /**
     * @brief Compares two SubscriptionPlan instances for equality.
     * @param other Plan to compare with.
     * @return true if tier and bitrate match.
     */
    bool operator==(const SubscriptionPlan& other) const;

    /**
     * @brief Compares two SubscriptionPlan instances for inequality.
     * @param other Plan to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const SubscriptionPlan& other) const;

    /**
     * @brief Stream output operator for formatting SubscriptionPlan info.
     * @param os Output stream.
     * @param plan Plan instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SubscriptionPlan& plan);


    /**
     * @brief Checks if subscription is expired against a given date string.
     * @param current_date Current date in YYYY.MM.DD format.
     * @return true if expired.
     * @throws LicenseExpiredException if license is expired.
     */
    bool CheckExpiration(const std::string& current_date) const;

    /**
     * @brief Upgrades subscription tier and features.
     * @param tier New tier name.
     * @param max_bitrate New maximum bitrate.
     * @param allows_offline Offline rights flag.
     * @param new_expiry New expiration date string.
     */
    void Upgrade(const std::string& tier, int max_bitrate, bool allows_offline, const std::string& new_expiry);

    /**
     * @brief Gets subscription tier name.
     * @return Reference to tier name string.
     */
    const std::string& GetTierName() const;

    /**
     * @brief Gets maximum allowed bitrate in kbps.
     * @return Bitrate integer.
     */
    int GetMaxBitrateKbps() const;

    /**
     * @brief Checks if offline caching and downloading is allowed.
     * @return true if allowed.
     */
    bool AllowsOffline() const;

    /**
     * @brief Gets expiration date string.
     * @return Reference to date string.
     */
    const std::string& GetExpiryDate() const;

private:
    std::string tier_name_;
    int max_bitrate_kbps_;
    bool allows_offline_;
    std::string expiry_date_;
};

#endif