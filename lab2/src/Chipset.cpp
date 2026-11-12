/**
 * @file Chipset.cpp
 * @brief Implementation of Chipset methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Chipset.h"
#include "ComputerException.h"

Chipset::Chipset(const std::string& model_name, int pcie_lanes, int sata_ports, int usb_ports) :
    model_name_(model_name), pcie_lanes_(pcie_lanes), sata_ports_(sata_ports), usb_ports_(usb_ports) {}

bool Chipset::operator==(const Chipset& other) const {
    return model_name_ == other.model_name_ && pcie_lanes_ == other.pcie_lanes_ &&
           sata_ports_ == other.sata_ports_ && usb_ports_ == other.usb_ports_;
}

bool Chipset::operator!=(const Chipset& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Chipset& chipset) {
    os << "Chipset " << chipset.model_name_ << " (" << chipset.pcie_lanes_ << " PCIe lanes, " << chipset.sata_ports_ << " SATA ports, " << chipset.usb_ports_ << " USB ports)";
    return os;
}

void Chipset::AllocatePcieLanes(int lanes) {
    if (lanes <= 0 || lanes > pcie_lanes_) 
        throw ComputerException("Insufficient chipset PCIe lanes available.");
    pcie_lanes_ -= lanes;
}

void Chipset::ReleasePcieLanes(int lanes) {
    if (lanes <= 0) 
        return;
    pcie_lanes_ += lanes;
}

bool Chipset::SupportsOverclocking() const {
    if (model_name_.empty()) 
        return false;
    char prefix = model_name_[0];
    if (prefix == 'Z' || prefix == 'X') 
        return true;
    if (model_name_.find("650") != std::string::npos || model_name_.find("670") != std::string::npos || model_name_.find("790") != std::string::npos) 
        return true;
    return false;
}

const std::string& Chipset::GetModelName() const {
    return model_name_;
}

int Chipset::GetPcieLanes() const {
    return pcie_lanes_;
}

int Chipset::GetSataPorts() const {
    return sata_ports_;
}

int Chipset::GetUsbPorts() const {
    return usb_ports_;
}
