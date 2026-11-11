/**
 * @file PCIeSlot.h
 * @brief Declaration of the PCIeSlot class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PCIE_SLOT_H
#define PCIE_SLOT_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a physical PCI Express expansion slot on the motherboard.
 */
class PCIeSlot {
public:
    /**
     * @brief Constructs a PCIe expansion slot with generation, physical lane width and state.
     * @param slot_index Zero-based physical slot identifier.
     * @param generation PCI Express specification generation ("PCIe 4.0", "PCIe 5.0").
     * @param lane_width Number of electrical lanes (16, 4, 1).
     * @param is_occupied Whether an expansion card is seated.
     * @param installed_device_name Name of currently installed expansion card.
     */
    explicit PCIeSlot(int slot_index = 0, const std::string& generation = "PCIe 4.0", int lane_width = 16, bool is_occupied = false, const std::string& installed_device_name = "");

    /**
     * @brief Compares two PCIe slots for equality.
     * @param other PCIeSlot instance to compare with.
     * @return true if slot attributes and occupied state match.
     */
    bool operator==(const PCIeSlot& other) const;

    /**
     * @brief Inequality operator.
     * @param other PCIeSlot instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PCIeSlot& other) const;

    /**
     * @brief Stream output operator for formatting PCIe slot info.
     * @param os Output stream.
     * @param slot PCIeSlot instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PCIeSlot& slot);

    /**
     * @brief Installs an expansion adapter card into this slot.
     * @param device_name Commercial model name of the expansion card.
     */
    void InstallDevice(const std::string& device_name);

    /**
     * @brief Removes the currently installed expansion card from the slot.
     */
    void RemoveDevice();

    /**
     * @brief Calculates theoretical unidirectional slot bandwidth in GB/s.
     * @return Peak bandwidth in GB/s.
     */
    double CalculateBandwidthGBs() const;

    /**
     * @brief Gets physical slot index.
     * @return Slot index.
     */
    int GetSlotIndex() const;

    /**
     * @brief Gets PCIe interface generation string.
     * @return Generation identifier.
     */
    const std::string& GetGeneration() const;

    /**
     * @brief Gets physical lane width (e.g. 16, 4, 1).
     * @return Lane width.
     */
    int GetLaneWidth() const;

    /**
     * @brief Checks whether the slot currently holds an installed card.
     * @return true if occupied.
     */
    bool IsOccupied() const;

    /**
     * @brief Gets the name of the installed expansion card.
     * @return Installed device name string reference.
     */
    const std::string& GetInstalledDeviceName() const;

private:
    int slot_index_;
    std::string generation_;
    int lane_width_;
    bool is_occupied_;
    std::string installed_device_name_;
};

#endif