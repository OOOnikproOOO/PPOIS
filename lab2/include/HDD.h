/**
 * @file HDD.h
 * @brief Declaration of the HDD class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef HDD_H
#define HDD_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a magnetic Hard Disk Drive (HDD) with spinning platters.
 */
class HDD {
public:
    /**
     * @brief Constructs an HDD with specified spindle and storage characteristics.
     * @param model Commercial model designation.
     * @param rpm Spindle rotational speed in revolutions per minute (5400, 7200).
     * @param capacity_gb Total disk storage capacity in gigabytes.
     * @param cache_mb On-board DRAM cache buffer in megabytes.
     */
    explicit HDD(const std::string& model = "Generic HDD", int rpm = 7200, int capacity_gb = 2000, int cache_mb = 128);

    /**
     * @brief Compares two HDDs for equality.
     * @param other HDD instance to compare.
     * @return true if model, RPM, and capacity match.
     */
    bool operator==(const HDD& other) const;

    /**
     * @brief Checks inequality.
     * @param other HDD instance to compare.
     * @return true if properties differ.
     */
    bool operator!=(const HDD& other) const;

    /**
     * @brief Stream output operator for formatting HDD specifications.
     * @param os Output stream.
     * @param hdd HDD instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const HDD& hdd);

    /**
     * @brief Parks read/write heads safely away from platters to prevent damage.
     */
    void ParkHeads();

    /**
     * @brief Spins up platters and unparks read/write heads.
     */
    void SpinUp();

    /**
     * @brief Writes data to the magnetic disk platters.
     * @param gigabytes Volume of data in gigabytes to write.
     * @return true if write succeeded.
     */
    bool WriteData(double gigabytes);

    /**
     * @brief Reads data from magnetic disk platters.
     * @param gigabytes Volume of data in gigabytes to read.
     * @return true if sufficient data is stored.
     */
    bool ReadData(double gigabytes);

    /**
     * @brief Scans disk surface sectors for media degradation and errors.
     * @param scanned_sectors Number of physical sectors to verify.
     */
    void ScanForBadSectors(int scanned_sectors);

    /**
     * @brief Gets HDD model name.
     * @return Model name string.
     */
    std::string GetModel() const;

    /**
     * @brief Gets spindle rotational speed in RPM.
     * @return Rotational speed.
     */
    int GetRpm() const;

    /**
     * @brief Gets total storage capacity in gigabytes.
     * @return Capacity in GB.
     */
    int GetCapacityGb() const;

    /**
     * @brief Gets currently used storage in gigabytes.
     * @return Used space in GB.
     */
    int GetUsedGb() const;

    /**
     * @brief Gets available free storage capacity in gigabytes.
     * @return Free space in GB.
     */
    int GetFreeSpaceGb() const;

    /**
     * @brief Gets on-board cache buffer size in megabytes.
     * @return Cache buffer in MB.
     */
    int GetCacheMb() const;

    /**
     * @brief Checks if heads are currently parked in safe landing zone.
     * @return true if heads are parked.
     */
    bool AreHeadsParked() const;

    /**
     * @brief Gets count of detected bad sectors.
     * @return Bad sector count.
     */
    int GetBadSectorsCount() const;

private:
    std::string model_;
    int rpm_;
    int capacity_gb_;
    int used_gb_;
    int cache_mb_;
    bool heads_parked_;
    int bad_sectors_count_;
};

#endif