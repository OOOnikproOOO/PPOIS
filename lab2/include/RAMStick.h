/**
 * @file RAMStick.h
 * @brief Declaration of the RAMStick class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef RAMSTICK_H
#define RAMSTICK_H

#include <iostream>
#include <string>
#include "RAMTiming.h"

/**
 * @brief Class modeling an individual physical Random Access Memory (RAM) stick.
 */
class RAMStick {
public:
    /**
     * @brief Constructs a RAM stick with specified specifications.
     * @param serial_number Hardware serial number.
     * @param capacity_mb Module capacity in megabytes.
     * @param frequency_mhz Base clock frequency in MHz.
     * @param generation DDR generation ("DDR4", "DDR5").
     * @param timings Primary sub-timings.
     */
    explicit RAMStick(const std::string& serial_number = "SN-RAM-001", int capacity_mb = 8192, int frequency_mhz = 3200, const std::string& generation = "DDR4", const RAMTiming& timings = RAMTiming());

    /**
     * @brief Compares two RAM sticks for equality based on serial and specifications.
     * @param other RAM stick to compare.
     * @return true if serial and properties match.
     */
    bool operator==(const RAMStick& other) const;

    /**
     * @brief Checks inequality.
     * @param other RAM stick to compare.
     * @return true if properties differ.
     */
    bool operator!=(const RAMStick& other) const;

    /**
     * @brief Stream output operator for formatting memory module information.
     * @param os Output stream.
     * @param stick RAM module instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const RAMStick& stick);

    /**
     * @brief Allocates and writes a specified block of data to memory.
     * @param megabytes Data volume in megabytes.
     * @return true if allocation succeeded.
     */
    bool WriteData(int megabytes);

    /**
     * @brief Reads a specified volume of previously written memory.
     * @param megabytes Data volume in megabytes to read.
     * @return true if requested data is currently stored.
     */
    bool ReadData(int megabytes);

    /**
     * @brief Activates an Extreme Memory Profile (XMP) overclock.
     * @param profile_frequency Boosted clock frequency in MHz.
     * @param profile_timings Tuned timing profile.
     */
    void EnableXMP(int profile_frequency, const RAMTiming& profile_timings);

    /**
     * @brief Executes memory cell integrity pattern diagnostics.
     * @return true if module passes integrity self-test.
     */
    bool RunDiagnostics() const;

    /**
     * @brief Clears and resets all allocated memory space.
     */
    void ClearMemory();

    /**
     * @brief Gets module serial number.
     * @return Serial number string.
     */
    std::string GetSerialNumber() const;

    /**
     * @brief Gets memory capacity in megabytes.
     * @return Capacity in MB.
     */
    int GetCapacityMb() const;

    /**
     * @brief Gets current operating frequency in MHz.
     * @return Frequency in MHz.
     */
    int GetFrequencyMhz() const;

    /**
     * @brief Gets DDR generation standard.
     * @return Generation string.
     */
    std::string GetGeneration() const;

    /**
     * @brief Gets current sub-timings.
     * @return Timing parameters.
     */
    const RAMTiming& GetTimings() const;

    /**
     * @brief Checks if XMP profile is currently active.
     * @return true if XMP is enabled.
     */
    bool IsXmpEnabled() const;

    /**
     * @brief Gets amount of currently allocated memory in megabytes.
     * @return Allocated memory in MB.
     */
    int GetUsedMb() const;

private:
    std::string serial_number_;
    int capacity_mb_;
    int frequency_mhz_;
    std::string generation_;
    RAMTiming timings_;
    bool xmp_enabled_;
    int used_mb_;
};

#endif