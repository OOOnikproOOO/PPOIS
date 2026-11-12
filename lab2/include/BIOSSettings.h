/**
 * @file BIOSSettings.h
 * @brief Declaration of the BIOSSettings class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef BIOSSETTINGS_H
#define BIOSSETTINGS_H

#include <iostream>
#include <string>

/**
 * @brief Represents motherboard BIOS/UEFI firmware configuration settings.
 */
class BIOSSettings {
public:
    /**
     * @brief Constructs a BIOSSettings configuration object.
     * @param boot_mode Boot mode ("UEFI" or "Legacy").
     * @param xmp_enabled Whether XMP memory overclocking profile is enabled.
     * @param secure_boot_enabled Whether Secure Boot verification is enabled.
     * @param fast_boot_enabled Whether Fast Boot POST skipping is enabled.
     */
    explicit BIOSSettings(const std::string& boot_mode = "UEFI", bool xmp_enabled = true, bool secure_boot_enabled = true, bool fast_boot_enabled = false);

    /**
     * @brief Equality operator comparing BIOS configuration flags.
     * @param other Another BIOSSettings instance.
     * @return true if all configuration fields match.
     */
    bool operator==(const BIOSSettings& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another BIOSSettings instance.
     * @return true if configurations differ.
     */
    bool operator!=(const BIOSSettings& other) const;

    /**
     * @brief Stream output operator for formatting BIOS settings.
     * @param os Output stream.
     * @param settings BIOSSettings instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const BIOSSettings& settings);

    /**
     * @brief Sets the firmware boot mode ("UEFI" or "Legacy").
     * @param mode Target boot mode string.
     */
    void SetBootMode(const std::string& mode);

    /**
     * @brief Enables or disables the XMP memory profile in BIOS.
     * @param enabled Target XMP state.
     */
    void ToggleXmp(bool enabled);

    /**
     * @brief Enables or disables Secure Boot verification.
     * @param enabled Target Secure Boot state.
     */
    void ToggleSecureBoot(bool enabled);

    /**
     * @brief Enables or disables Fast Boot initialization.
     * @param enabled Target Fast Boot state.
     */
    void SetFastBoot(bool enabled);

    /**
     * @brief Validates compatibility of active BIOS configuration flags.
     * @return true if firmware configuration is valid.
     */
    bool ValidateBootConfig() const;

    /**
     * @brief Gets active boot mode string.
     * @return Boot mode ("UEFI" or "Legacy").
     */
    const std::string& GetBootMode() const;

    /**
     * @brief Checks whether XMP profile is enabled.
     * @return true if enabled.
     */
    bool IsXmpEnabled() const;

    /**
     * @brief Checks whether Secure Boot is enabled.
     * @return true if enabled.
     */
    bool IsSecureBootEnabled() const;

    /**
     * @brief Checks whether Fast Boot is enabled.
     * @return true if enabled.
     */
    bool IsFastBootEnabled() const;

private:
    std::string boot_mode_;
    bool xmp_enabled_;
    bool secure_boot_enabled_;
    bool fast_boot_enabled_;
};

#endif