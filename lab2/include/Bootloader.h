/**
 * @file Bootloader.h
 * @brief Declaration of the Bootloader class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <iostream>
#include <string>
#include "BIOSSettings.h"

/**
 * @brief Represents the system bootloader responsible for verifying BIOS settings and loading the OS kernel.
 */
class Bootloader {
public:
    /**
     * @brief Constructs a Bootloader instance.
     * @param bootloader_name Name of the bootloader (e.g., GRUB2, Windows Boot Manager).
     * @param timeout_seconds Boot menu countdown timeout in seconds.
     * @param is_verified Whether kernel signature/config has been verified.
     * @param bios_settings Associated motherboard BIOS settings.
     */
    explicit Bootloader(const std::string& bootloader_name = "GRUB2", int timeout_seconds = 5, bool is_verified = false, const BIOSSettings& bios_settings = BIOSSettings());

    /**
     * @brief Equality operator comparing bootloader configurations.
     * @param other Another Bootloader instance.
     * @return true if bootloaders match.
     */
    bool operator==(const Bootloader& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another Bootloader instance.
     * @return true if bootloaders differ.
     */
    bool operator!=(const Bootloader& other) const;

    /**
     * @brief Stream output operator for formatting bootloader state.
     * @param os Output stream.
     * @param bootloader Bootloader instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Bootloader& bootloader);

    /**
     * @brief Sets the boot menu countdown timeout in seconds.
     * @param seconds Timeout duration (0 to 60 seconds).
     */
    void SetTimeout(int seconds);

    /**
     * @brief Validates BIOS settings and verifies the kernel image before booting.
     * @return true if verification succeeds.
     */
    bool VerifyAndLoadKernel();

    /**
     * @brief Resets the kernel verification status flag.
     */
    void ResetVerification();

    /**
     * @brief Gets bootloader name.
     * @return Bootloader name string.
     */
    const std::string& GetBootloaderName() const;

    /**
     * @brief Gets boot menu timeout in seconds.
     * @return Timeout in seconds.
     */
    int GetTimeoutSeconds() const;

    /**
     * @brief Checks whether the kernel has been verified.
     * @return true if verified.
     */
    bool IsVerified() const;

    /**
     * @brief Gets reference to the associated BIOS settings.
     * @return Reference to BIOSSettings.
     */
    BIOSSettings& GetBiosSettings();
    const BIOSSettings& GetBiosSettings() const;

private:
    std::string bootloader_name_;
    int timeout_seconds_;
    bool is_verified_;
    BIOSSettings bios_settings_;
};

#endif