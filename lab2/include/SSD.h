/**
 * @file SSD.h
 * @brief Declaration of the SSD class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SSD_H
#define SSD_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a Solid State Drive (SSD) with flash memory.
 */
class SSD {
public:
    /**
     * @brief Constructs an SSD with specified hardware characteristics.
     * @param model Commercial model name.
     * @param interface_type Interface standard (e.g., "NVMe PCIe 4.0", "SATA 3").
     * @param capacity_gb Total storage capacity in gigabytes.
     * @param tbw_resource_tb Terabytes Written (TBW) endurance rating.
     */
    explicit SSD(const std::string& model = "Generic NVMe SSD", const std::string& interface_type = "NVMe PCIe 4.0", int capacity_gb = 1000, double tbw_resource_tb = 600.0);

    /**
     * @brief Compares two SSDs for equality.
     * @param other SSD instance to compare.
     * @return true if model, interface, and capacity match.
     */
    bool operator==(const SSD& other) const;

    /**
     * @brief Checks inequality.
     * @param other SSD instance to compare.
     * @return true if properties differ.
     */
    bool operator!=(const SSD& other) const;

    /**
     * @brief Stream output operator for formatting SSD specifications.
     * @param os Output stream.
     * @param ssd SSD instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SSD& ssd);

    /**
     * @brief Writes data to the SSD, advancing NAND flash write endurance counters.
     * @param gigabytes Volume of data to write in gigabytes.
     * @return true if write succeeded.
     */
    bool WriteData(double gigabytes);

    /**
     * @brief Reads data from the SSD.
     * @param gigabytes Volume of data in gigabytes to read.
     * @return true if sufficient data is stored.
     */
    bool ReadData(double gigabytes);

    /**
     * @brief Executes NAND TRIM command to clear unused memory blocks.
     */
    void PerformTrim();

    /**
     * @brief Evaluates S.M.A.R.T. flash wear health percentage.
     */
    void RunHealthCheck();

    /**
     * @brief Estimates remaining operational drive lifespan in months.
     * @param avg_write_gb_per_day Estimated daily write workload.
     * @return Estimated remaining lifespan in months.
     */
    double EstimateRemainingLifespanMonths(double avg_write_gb_per_day) const;

    /**
     * @brief Gets SSD model name.
     * @return Model name string.
     */
    std::string GetModel() const;

    /**
     * @brief Gets host interface standard.
     * @return Interface type.
     */
    std::string GetInterfaceType() const;

    /**
     * @brief Gets total storage capacity in gigabytes.
     * @return Capacity in GB.
     */
    int GetCapacityGb() const;

    /**
     * @brief Gets currently used storage in gigabytes.
     * @return Used storage in GB.
     */
    int GetUsedGb() const;

    /**
     * @brief Gets available free storage capacity in gigabytes.
     * @return Free space in GB.
     */
    int GetFreeSpaceGb() const;

    /**
     * @brief Gets total manufacturer rated TBW endurance.
     * @return TBW rating in Terabytes.
     */
    double GetTbwResourceTb() const;

    /**
     * @brief Gets accumulated Terabytes written over drive lifetime.
     * @return Written Terabytes.
     */
    double GetTbwWrittenTb() const;

    /**
     * @brief Gets health percentage (100% brand new down to 0%).
     * @return Health percentage.
     */
    int GetHealthPercentage() const;

private:
    std::string model_;
    std::string interface_type_;
    int capacity_gb_;
    int used_gb_;
    double tbw_resource_tb_;
    double tbw_written_tb_;
    int health_percentage_;
};

#endif