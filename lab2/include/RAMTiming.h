/**
 * @file RAMTiming.h
 * @brief Declaration of the RAMTiming class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef RAMTIMING_H
#define RAMTIMING_H

#include <iostream>

/**
 * @brief Class modeling memory operational sub-timings (CL-tRCD-tRP-tRAS-CR).
 */
class RAMTiming {
public:
    /**
     * @brief Constructs RAM timings with standard XMP parameters.
     * @param cas_latency Column Address Strobe (CAS) latency in clock cycles.
     * @param trcd RAS to CAS delay cycles.
     * @param trp Row Precharge delay cycles.
     * @param tras Row Active time cycles.
     * @param command_rate Command Rate (1T or 2T).
     */
    explicit RAMTiming(int cas_latency = 16, int trcd = 18, int trp = 18, int tras = 36, int command_rate = 1);

    /**
     * @brief Equality operator comparing timing parameters.
     * @param other Timing object to compare.
     * @return true if all primary timings match.
     */
    bool operator==(const RAMTiming& other) const;

    /**
     * @brief Inequality operator.
     * @param other Timing object to compare.
     * @return true if any timing differs.
     */
    bool operator!=(const RAMTiming& other) const;

    /**
     * @brief Stream output operator for formatting timings string (e.g., 16-18-18-36).
     * @param os Output stream.
     * @param timing Timing instance to format.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const RAMTiming& timing);

    /**
     * @brief Calculates absolute access latency in nanoseconds.
     * @param frequency_mhz Operating memory frequency in MHz.
     * @return Real latency in nanoseconds.
     */
    double CalculateTrueLatencyNs(int frequency_mhz) const;

    /**
     * @brief Validates stability relationship between sub-timings.
     * @return true if timings satisfy hardware constraints.
     */
    bool ValidateTimings() const;

    /**
     * @brief Adjusts timings automatically for target memory clock.
     * @param target_freq_mhz Desired operating frequency in MHz.
     */
    void OptimizeForFrequency(int target_freq_mhz);

    /**
     * @brief Determines whether this timing configuration yields lower latency than another.
     * @param other Competitor timing settings.
     * @param freq_this Operating frequency for this timing.
     * @param freq_other Operating frequency for other timing.
     * @return true if this configuration has lower true latency.
     */
    bool IsFasterThan(const RAMTiming& other, int freq_this, int freq_other) const;

    /**
     * @brief Gets CAS Latency.
     * @return CAS latency cycles.
     */
    int GetCasLatency() const;

    /**
     * @brief Gets RAS to CAS delay.
     * @return tRCD cycles.
     */
    int GetTrcd() const;

    /**
     * @brief Gets Row Precharge delay.
     * @return tRP cycles.
     */
    int GetTrp() const;

    /**
     * @brief Gets Row Active time.
     * @return tRAS cycles.
     */
    int GetTras() const;

    /**
     * @brief Gets Command Rate.
     * @return Command rate (1 or 2).
     */
    int GetCommandRate() const;

private:
    int cas_latency_;
    int trcd_;
    int trp_;
    int tras_;
    int command_rate_;
};

#endif