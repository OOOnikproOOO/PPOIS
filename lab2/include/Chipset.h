/**
 * @file Chipset.h
 * @brief Declaration of the Chipset class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef CHIPSET_H
#define CHIPSET_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a Motherboard Platform Controller Hub (PCH) chipset.
 */
class Chipset {
public:
    /**
     * @brief Constructs a Chipset with specified model, PCIe lanes, SATA and USB ports.
     * @param model_name Commercial chipset model identifier.
     * @param pcie_lanes Available chipset PCI Express lanes.
     * @param sata_ports Number of integrated SATA storage ports.
     * @param usb_ports Number of supported USB controller ports.
     */
    explicit Chipset(const std::string& model_name = "AMD B650", int pcie_lanes = 36, int sata_ports = 4, int usb_ports = 10);

    /**
     * @brief Compares two chipsets for equality.
     * @param other Chipset instance to compare with.
     * @return true if model and lane/port counts match.
     */
    bool operator==(const Chipset& other) const;

    /**
     * @brief Inequality operator.
     * @param other Chipset instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const Chipset& other) const;

    /**
     * @brief Stream output operator for formatting chipset specification.
     * @param os Output stream.
     * @param chipset Chipset instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Chipset& chipset);

    /**
     * @brief Allocates a specified number of PCIe lanes to a peripheral device.
     * @param lanes Number of PCIe lanes requested.
     */
    void AllocatePcieLanes(int lanes);

    /**
     * @brief Releases previously allocated PCIe lanes back to the chipset pool.
     * @param lanes Number of PCIe lanes to release.
     */
    void ReleasePcieLanes(int lanes);

    /**
     * @brief Checks whether this chipset supports CPU and memory overclocking.
     * @return true if overclocking is supported.
     */
    bool SupportsOverclocking() const;

    /**
     * @brief Gets chipset commercial model name.
     * @return Model name string reference.
     */
    const std::string& GetModelName() const;

    /**
     * @brief Gets remaining available PCIe lanes.
     * @return Available PCIe lane count.
     */
    int GetPcieLanes() const;

    /**
     * @brief Gets total count of integrated SATA ports.
     * @return SATA port count.
     */
    int GetSataPorts() const;

    /**
     * @brief Gets total count of integrated USB ports.
     * @return USB port count.
     */
    int GetUsbPorts() const;

private:
    std::string model_name_;
    int pcie_lanes_;
    int sata_ports_;
    int usb_ports_;
};

#endif