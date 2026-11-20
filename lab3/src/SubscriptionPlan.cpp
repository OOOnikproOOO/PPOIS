/**
 * @file SubscriptionPlan.cpp
 * @brief Implementation of SubscriptionPlan methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SubscriptionPlan.h"
#include "LicenseExpiredException.h"
#include <sstream>

SubscriptionPlan::SubscriptionPlan(const std::string& tier_name, int max_bitrate_kbps, bool allows_offline, const std::string& expiry_date) :
    tier_name_(tier_name), max_bitrate_kbps_(max_bitrate_kbps < 128 ? 128 : (max_bitrate_kbps > 1411 ? 1411 : max_bitrate_kbps)), allows_offline_(allows_offline), expiry_date_(expiry_date) {}

bool SubscriptionPlan::operator==(const SubscriptionPlan& other) const {
    return tier_name_ == other.tier_name_ &&
           max_bitrate_kbps_ == other.max_bitrate_kbps_ &&
           allows_offline_ == other.allows_offline_ &&
           expiry_date_ == other.expiry_date_;
}

bool SubscriptionPlan::operator!=(const SubscriptionPlan& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SubscriptionPlan& plan) {
    os << "SubscriptionPlan[" << plan.tier_name_ << " (Max: " << plan.max_bitrate_kbps_ << " kbps), Offline: " << (plan.allows_offline_ ? "YES" : "NO") << ", Expires: " << plan.expiry_date_ << "]";
    return os;
}


bool SubscriptionPlan::CheckExpiration(const std::string& current_date) const {
    if (current_date > expiry_date_)
        throw LicenseExpiredException("Subscription tier " + tier_name_ + " expired on " + expiry_date_ + " (current date: " + current_date + ").");

    return false;
}

void SubscriptionPlan::Upgrade(const std::string& tier, int max_bitrate, bool allows_offline, const std::string& new_expiry) {
    tier_name_ = tier;
    max_bitrate_kbps_ = max_bitrate < 128 ? 128 : (max_bitrate > 1411 ? 1411 : max_bitrate);
    allows_offline_ = allows_offline;
    expiry_date_ = new_expiry;
}

const std::string& SubscriptionPlan::GetTierName() const {
    return tier_name_;
}

int SubscriptionPlan::GetMaxBitrateKbps() const {
    return max_bitrate_kbps_;
}

bool SubscriptionPlan::AllowsOffline() const {
    return allows_offline_;
}

const std::string& SubscriptionPlan::GetExpiryDate() const {
    return expiry_date_;
}