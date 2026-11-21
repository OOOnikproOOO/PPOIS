/**
 * @file StorageController.h
 * @brief Declaration of the StorageController class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef STORAGECONTROLLER_H
#define STORAGECONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include "HDD.h"
#include "SSD.h"

/**
 * @brief Class modeling a storage host controller managing SSD and HDD drives and RAID configurations.
 */
class StorageController {
public:
    /**
     * @brief Constructs a storage controller with specified interface type.
     * @param controller_type Controller hardware interface (e.g., "NVMe-AHCI-Hybrid").
     */
    explicit StorageController(const std::string& controller_type = "NVMe-AHCI-Hybrid");

    /**
     * @brief Compares two controllers for equality.
     * @param other Controller to compare.
     * @return true if controller type and RAID configuration match.
     */
    bool operator==(const StorageController& other) const;

    /**
     * @brief Checks inequality.
     * @param other Controller to compare.
     * @return true if properties differ.
     */
    bool operator!=(const StorageController& other) const;

    /**
     * @brief Stream output operator for formatting storage controller summary.
     * @param os Output stream.
     * @param controller StorageController instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const StorageController& controller);

    /**
     * @brief Attaches a Solid State Drive to the controller.
     * @param drive SSD instance to attach.
     */
    void AttachSSD(const SSD& drive);

    /**
     * @brief Attaches a Hard Disk Drive to the controller.
     * @param drive HDD instance to attach.
     */
    void AttachHDD(const HDD& drive);

    /**
     * @brief Configures RAID operational array mode ("NONE", "RAID0", "RAID1", "JBOD").
     * @param mode Target RAID mode string.
     */
    void ConfigureRAID(const std::string& mode);

    /**
     * @brief Computes combined usable storage capacity according to active RAID mode.
     * @return Total usable capacity in gigabytes.
     */
    double GetTotalCapacityGb() const;

    /**
     * @brief Verifies integrity and health status across all attached physical storage drives.
     * @return true if all drives and RAID array pass health inspection.
     */
    bool PerformIntegrityCheck();

    /**
     * @brief Gets controller architecture type string.
     * @return Controller type.
     */
    std::string GetControllerType() const;

    /**
     * @brief Gets currently configured RAID mode.
     * @return RAID mode string.
     */
    std::string GetRaidMode() const;

    /**
     * @brief Gets count of attached Solid State Drives.
     * @return Number of SSDs.
     */
    int GetSsdCount() const;

    /**
     * @brief Gets count of attached Hard Disk Drives.
     * @return Number of HDDs.
     */
    int GetHddCount() const;

    /**
     * @brief Checks whether the RAID array is healthy and operational.
     * @return true if array is healthy.
     */
    bool IsRaidHealthy() const;

private:
    std::string controller_type_;
    std::string raid_mode_;
    std::vector<SSD> ssds_;
    std::vector<HDD> hdds_;
    bool is_raid_healthy_;
};

#endif