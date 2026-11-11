/**
 * @file Motherboard.h
 * @brief Declaration of the Motherboard class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include "VRM.h"
#include "Chipset.h"
#include "PCIeSlot.h"

/**
 * @brief Class modeling the main system motherboard interconnecting VRM, chipset and PCIe expansion slots.
 */
class Motherboard {
public:
    /**
     * @brief Constructs a Motherboard with specified model, form factor, BIOS, VRM and chipset.
     * @param model_name Commercial motherboard name.
     * @param form_factor Physical PCB size ("ATX", "Micro-ATX", "Mini-ITX").
     * @param bios_version Installed firmware version string.
     * @param vrm Integrated CPU voltage regulator module.
     * @param chipset Integrated platform controller hub chipset.
     */
    explicit Motherboard(const std::string& model_name = "ASUS ROG STRIX B650-E", const std::string& form_factor = "ATX", const std::string& bios_version = "v1.40", const VRM& vrm = VRM(), const Chipset& chipset = Chipset());

    /**
     * @brief Compares two motherboards for equality.
     * @param other Motherboard instance to compare with.
     * @return true if model, BIOS, VRM, and chipset match.
     */
    bool operator==(const Motherboard& other) const;

    /**
     * @brief Inequality operator.
     * @param other Motherboard instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const Motherboard& other) const;

    /**
     * @brief Stream output operator for formatting motherboard configuration.
     * @param os Output stream.
     * @param motherboard Motherboard instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Motherboard& motherboard);

    /**
     * @brief Adds a PCIe expansion slot to the motherboard layout.
     * @param slot PCIeSlot instance to register.
     */
    void AddSlot(const PCIeSlot& slot);

    /**
     * @brief Updates the motherboard BIOS firmware version.
     * @param new_version Target BIOS firmware version string.
     */
    void FlashBios(const std::string& new_version);

    /**
     * @brief Runs Power-On Self-Test (POST) hardware diagnostics on boot.
     * @return true if all critical power and thermal checks pass.
     */
    bool PerformPOST() const;

    /**
     * @brief Gets motherboard commercial model name.
     * @return Model name string reference.
     */
    const std::string& GetModelName() const;

    /**
     * @brief Gets motherboard physical form factor.
     * @return Form factor string reference.
     */
    const std::string& GetFormFactor() const;

    /**
     * @brief Gets current BIOS firmware version string.
     * @return BIOS version string reference.
     */
    const std::string& GetBiosVersion() const;

    /**
     * @brief Gets total number of installed PCIe expansion slots.
     * @return Slot count.
     */
    int GetSlotCount() const;

    /**
     * @brief Gets reference to the integrated VRM unit.
     * @return Reference to VRM.
     */
    VRM& GetVRM();
    const VRM& GetVRM() const;

    /**
     * @brief Gets reference to the integrated Chipset unit.
     * @return Reference to Chipset.
     */
    Chipset& GetChipset();
    const Chipset& GetChipset() const;

    /**
     * @brief Gets reference to a PCIe slot at the specified index.
     * @param index Slot index.
     * @return Reference to PCIeSlot.
     */
    PCIeSlot& GetSlot(int index);
    const PCIeSlot& GetSlot(int index) const;

private:
    std::string model_name_;
    std::string form_factor_;
    std::string bios_version_;
    VRM vrm_;
    Chipset chipset_;
    std::vector<PCIeSlot> pcie_slots_;
};

#endif