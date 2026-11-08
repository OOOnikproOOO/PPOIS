/**
 * @file RAM.h
 * @brief Declaration of the RAM class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef RAM_H
#define RAM_H

#include <iostream>
#include <vector>
#include "RAMStick.h"

/**
 * @brief Class managing physical RAM DIMM slots and multi-channel memory allocations.
 */
class RAM {
public:
    /**
     * @brief Constructs a memory subsystem with specified slot capacity.
     * @param max_slots Total available DIMM slots on the motherboard.
     */
    explicit RAM(int max_slots = 4);

    /**
     * @brief Compares two RAM subsystems for equality.
     * @param other Memory subsystem to compare.
     * @return true if slot count, sticks, and channel configuration match.
     */
    bool operator==(const RAM& other) const;

    /**
     * @brief Checks inequality.
     * @param other Memory subsystem to compare.
     * @return true if configurations differ.
     */
    bool operator!=(const RAM& other) const;

    /**
     * @brief Stream output operator for formatting memory subsystem summary.
     * @param os Output stream.
     * @param ram Memory subsystem instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const RAM& ram);

    /**
     * @brief Installs a RAM module into an available motherboard slot.
     * @param stick Memory stick to install.
     * @param slot_index Target slot index.
     */
    void InstallStick(const RAMStick& stick, int slot_index);

    /**
     * @brief Removes a RAM module from a motherboard slot.
     * @param slot_index Target slot index.
     * @return Removed RAM module.
     */
    RAMStick RemoveStick(int slot_index);

    /**
     * @brief Allocates a block of system memory across installed sticks.
     * @param megabytes Memory volume in megabytes to allocate.
     * @return true if allocation succeeded.
     */
    bool Allocate(int megabytes);

    /**
     * @brief Releases previously allocated system memory.
     * @param megabytes Memory volume in megabytes to free.
     */
    void Free(int megabytes);

    /**
     * @brief Calculates total combined capacity across all installed modules.
     * @return Combined capacity in megabytes.
     */
    int GetTotalCapacityMb() const;

    /**
     * @brief Gets a copy of the RAM stick at specified slot index.
     * @param slot_index Target slot index.
     * @return RAMStick instance.
     */
    RAMStick GetStick(int slot_index) const;

    /**
     * @brief Gets total number of motherboard DIMM slots.
     * @return Maximum slots.
     */
    int GetMaxSlots() const;

    /**
     * @brief Gets count of currently populated slots.
     * @return Number of installed sticks.
     */
    int GetInstalledSticksCount() const;

    /**
     * @brief Gets current active multi-channel mode (1 = Single, 2 = Dual, 4 = Quad).
     * @return Channel multiplier.
     */
    int GetChannelMode() const;

    /**
     * @brief Gets total allocated memory in megabytes.
     * @return Currently used memory in MB.
     */
    int GetTotalAllocatedMb() const;

private:
    void UpdateChannelMode();

    int max_slots_;
    std::vector<RAMStick> sticks_;
    int channel_mode_;
    int total_allocated_mb_;
};

#endif