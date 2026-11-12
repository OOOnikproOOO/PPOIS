/**
 * @file Bootloader.cpp
 * @brief Implementation of Bootloader methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Bootloader.h"
#include "ComputerException.h"

Bootloader::Bootloader(const std::string& bootloader_name, int timeout_seconds, bool is_verified, const BIOSSettings& bios_settings) :
    bootloader_name_(bootloader_name), timeout_seconds_(timeout_seconds), is_verified_(is_verified), bios_settings_(bios_settings) {}

bool Bootloader::operator==(const Bootloader& other) const {
    return bootloader_name_ == other.bootloader_name_ && timeout_seconds_ == other.timeout_seconds_ &&
           is_verified_ == other.is_verified_ && bios_settings_ == other.bios_settings_;
}

bool Bootloader::operator!=(const Bootloader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Bootloader& bootloader) {
    os << "Bootloader " << bootloader.bootloader_name_ << " (Timeout: " << bootloader.timeout_seconds_ << "s, Verified: " << (bootloader.is_verified_ ? "YES" : "NO") << ", " << bootloader.bios_settings_ << ")";
    return os;
}

void Bootloader::SetTimeout(int seconds) {
    if (seconds < 0 || seconds > 60) 
        throw ComputerException("Bootloader timeout must be between 0 and 60 seconds.");
    timeout_seconds_ = seconds;
}

bool Bootloader::VerifyAndLoadKernel() {
    bios_settings_.ValidateBootConfig();
    is_verified_ = true;
    return true;
}

void Bootloader::ResetVerification() {
    is_verified_ = false;
}

const std::string& Bootloader::GetBootloaderName() const {
    return bootloader_name_;
}

int Bootloader::GetTimeoutSeconds() const {
    return timeout_seconds_;
}

bool Bootloader::IsVerified() const {
    return is_verified_;
}

BIOSSettings& Bootloader::GetBiosSettings() {
    return bios_settings_;
}

const BIOSSettings& Bootloader::GetBiosSettings() const {
    return bios_settings_;
}