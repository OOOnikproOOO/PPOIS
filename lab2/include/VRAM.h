/**
 * @file VRAM.h
 * @brief Declaration of the VRAM class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef VRAM_H
#define VRAM_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling Video Random Access Memory (VRAM).
 */
class VRAM {
public:
    /**
     * @brief Constructs VRAM with specified capacity and bus width.
     * @param capacity_mb Video memory capacity in megabytes.
     * @param bus_width_bits Memory interface bus width in bits (e.g. 128, 256, 384).
     * @param memory_type Technology standard ("GDDR6", "GDDR6X").
     */
    explicit VRAM(int capacity_mb = 16384, int bus_width_bits = 256, const std::string& memory_type = "GDDR6");

    /**
     * @brief Compares two VRAM configurations for equality.
     * @param other VRAM instance to compare.
     * @return true if capacity, bus width, and type match.
     */
    bool operator==(const VRAM& other) const;

    /**
     * @brief Inequality operator.
     * @param other VRAM instance to compare.
     * @return true if properties differ.
     */
    bool operator!=(const VRAM& other) const;

    /**
     * @brief Stream output operator for formatting VRAM info.
     * @param os Output stream.
     * @param vram VRAM instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const VRAM& vram);

    /**
     * @brief Allocates video memory buffer for frame textures.
     * @param megabytes Data volume in megabytes to allocate.
     * @return true on successful allocation.
     */
    bool Allocate(int megabytes);

    /**
     * @brief Releases previously allocated video memory buffer.
     * @param megabytes Data volume in megabytes to free.
     */
    void Free(int megabytes);

    /**
     * @brief Calculates theoretical peak memory bandwidth in Gigabytes per second.
     * @param memory_clock_mhz Effective memory clock in MHz.
     * @return Bandwidth in GB/s.
     */
    double CalculateBandwidthGbps(int memory_clock_mhz) const;

    /**
     * @brief Gets total capacity in megabytes.
     * @return Total capacity in MB.
     */
    int GetCapacityMb() const;

    /**
     * @brief Gets interface bus width in bits.
     * @return Bus width.
     */
    int GetBusWidthBits() const;

    /**
     * @brief Gets currently allocated video memory in megabytes.
     * @return Used memory in MB.
     */
    int GetUsedMb() const;

    /**
     * @brief Gets memory generation technology string.
     * @return Memory type name.
     */
    std::string GetMemoryType() const;

private:
    int capacity_mb_;
    int bus_width_bits_;
    int used_mb_;
    std::string memory_type_;
};

#endif