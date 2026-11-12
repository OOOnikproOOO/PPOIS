/**
 * @file BIOSSettings.cpp
 * @brief Implementation of BIOSSettings methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "BIOSSettings.h"
#include "ComputerException.h"
#include "POSTFailureException.h"

BIOSSettings::BIOSSettings(const std::string& boot_mode, bool xmp_enabled, bool secure_boot_enabled, bool fast_boot_enabled) :
    boot_mode_(boot_mode), xmp_enabled_(xmp_enabled), secure_boot_enabled_(secure_boot_enabled), fast_boot_enabled_(fast_boot_enabled) {}

bool BIOSSettings::operator==(const BIOSSettings& other) const {
    return boot_mode_ == other.boot_mode_ && xmp_enabled_ == other.xmp_enabled_ &&
           secure_boot_enabled_ == other.secure_boot_enabled_ && fast_boot_enabled_ == other.fast_boot_enabled_;
}

bool BIOSSettings::operator!=(const BIOSSettings& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const BIOSSettings& settings) {
    os << "BIOSSettings [" << settings.boot_mode_ << ", XMP: " << (settings.xmp_enabled_ ? "ON" : "OFF") << ", SecureBoot: " << (settings.secure_boot_enabled_ ? "ON" : "OFF") << ", FastBoot: " << (settings.fast_boot_enabled_ ? "ON" : "OFF") << "]";
    return os;
}

void BIOSSettings::SetBootMode(const std::string& mode) {
    if (mode != "UEFI" && mode != "Legacy") 
        throw ComputerException("Unsupported BIOS boot mode: '" + mode + "'. Use UEFI or Legacy.");
    boot_mode_ = mode;
}

void BIOSSettings::ToggleXmp(bool enabled) {
    xmp_enabled_ = enabled;
}

void BIOSSettings::ToggleSecureBoot(bool enabled) {
    secure_boot_enabled_ = enabled;
}

void BIOSSettings::SetFastBoot(bool enabled) {
    fast_boot_enabled_ = enabled;
}

bool BIOSSettings::ValidateBootConfig() const {
    if (secure_boot_enabled_ && boot_mode_ == "Legacy") 
        throw POSTFailureException("Secure Boot cannot be enabled in Legacy BIOS mode.");
    return true;
}

const std::string& BIOSSettings::GetBootMode() const {
    return boot_mode_;
}

bool BIOSSettings::IsXmpEnabled() const {
    return xmp_enabled_;
}

bool BIOSSettings::IsSecureBootEnabled() const {
    return secure_boot_enabled_;
}

bool BIOSSettings::IsFastBootEnabled() const {
    return fast_boot_enabled_;
}