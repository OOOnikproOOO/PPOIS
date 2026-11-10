/**
 * @file CPU.h
 * @brief Declaration of the CPU class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include <vector>
#include "CPUCache.h"
#include "CPUCore.h"

/**
 * @brief Class modeling a multi-core Central Processing Unit (CPU).
 */
class CPU {
public:
    /**
     * @brief Constructs a CPU with specified model, socket, and TDP.
     * @param model_name Processor commercial name.
     * @param socket_type Physical socket interface (e.g., LGA1700, AM5).
     * @param tdp_watts Thermal Design Power in Watts.
     * @param l3_cache_size_kb Shared Level 3 cache size in KB.
     */
    explicit CPU(const std::string& model_name = "Generic CPU", const std::string& socket_type = "AM5", int tdp_watts = 65, int l3_cache_size_kb = 16384);

    /**
     * @brief Compares two CPUs for equality.
     * @param other Processor to compare with.
     * @return true if model, socket, and TDP match.
     */
    bool operator==(const CPU& other) const;

    /**
     * @brief Compares two CPUs for inequality.
     * @param other Processor to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const CPU& other) const;

    /**
     * @brief Stream output operator for formatting CPU info.
     * @param os Output stream.
     * @param cpu CPU instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const CPU& cpu);

    /**
     * @brief Adds an execution core to the processor.
     * @param core Core instance to install.
     */
    void AddCore(const CPUCore& core);

    /**
     * @brief Distributes a computational task across all available cores.
     * @param total_instructions Total instruction count to execute.
     */
    void ComputeWorkload(long long total_instructions);

    /**
     * @brief Applies an overclocking multiplier across all cores.
     * @param multiplier Frequency multiplier greater than 1.0.
     */
    void Overclock(double multiplier);

    /**
     * @brief Computes the average temperature across all physical cores.
     * @return Mean temperature in degrees Celsius.
     */
    double GetAverageTemperature() const;

    /**
     * @brief Estimates current power consumption in Watts.
     * @return Dynamic power draw in Watts.
     */
    int CalculateCurrentPowerDraw() const;

    /**
     * @brief Gets model name string.
     * @return Processor model.
     */
    std::string GetModelName() const;

    /**
     * @brief Gets socket type string.
     * @return Socket identifier.
     */
    std::string GetSocketType() const;

    /**
     * @brief Gets base Thermal Design Power in Watts.
     * @return TDP rating.
     */
    int GetTdpWatts() const;

    /**
     * @brief Lowers processor temperature across all execution cores.
     * @param delta_celsius Degrees Celsius to decrease.
     */
    void CoolDown(double delta_celsius);

    /**
     * @brief Gets total number of installed cores.
     * @return Core count.
     */
    int GetCoreCount() const;

    /**
     * @brief Gets a reference to an individual physical execution core.
     * @param index Core index.
     * @return Reference to CPUCore.
     */
    CPUCore& GetCore(int index);
    const CPUCore& GetCore(int index) const;

    /**
     * @brief Gets reference to shared L3 cache.
     * @return Reference to shared L3 cache object.
     */
    CPUCache& GetL3Cache();
    const CPUCache& GetL3Cache() const;

    /**
     * @brief Checks if processor is running with overclock profile.
     * @return true if overclocked.
     */
    bool IsOverclocked() const;

private:
    std::string model_name_;
    std::string socket_type_;
    int tdp_watts_;
    std::vector<CPUCore> cores_;
    CPUCache l3_cache_;
    bool is_overclocked_;
};

#endif