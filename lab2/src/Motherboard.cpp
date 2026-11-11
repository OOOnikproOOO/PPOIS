/**
 * @file Motherboard.cpp
 * @brief Implementation of Motherboard methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Motherboard.h"
#include "Exceptions.h"

Motherboard::Motherboard(const std::string& model_name, const std::string& form_factor, const std::string& bios_version, const VRM& vrm, const Chipset& chipset) :
    model_name_(model_name), form_factor_(form_factor), bios_version_(bios_version), vrm_(vrm), chipset_(chipset) {}

bool Motherboard::operator==(const Motherboard& other) const {
    return model_name_ == other.model_name_ && form_factor_ == other.form_factor_ &&
           bios_version_ == other.bios_version_ && vrm_ == other.vrm_ && chipset_ == other.chipset_;
}

bool Motherboard::operator!=(const Motherboard& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Motherboard& motherboard) {
    os << "Motherboard " << motherboard.model_name_ << " [" << motherboard.form_factor_ << ", BIOS: " << motherboard.bios_version_ << ", " << motherboard.vrm_ << ", " << motherboard.chipset_ << "]";
    return os;
}

void Motherboard::AddSlot(const PCIeSlot& slot) {
    pcie_slots_.push_back(slot);
}

void Motherboard::FlashBios(const std::string& new_version) {
    if (new_version.empty()) 
        throw ComputerException("BIOS version string cannot be empty.");
    bios_version_ = new_version;
}

bool Motherboard::PerformPOST() const {
    if (vrm_.GetTemperatureCelsius() > 105.0) 
        throw POSTFailureException("Motherboard POST failure: VRM temperature critical (> 105 °C).");
    return true;
}

const std::string& Motherboard::GetModelName() const {
    return model_name_;
}

const std::string& Motherboard::GetFormFactor() const {
    return form_factor_;
}

const std::string& Motherboard::GetBiosVersion() const {
    return bios_version_;
}

int Motherboard::GetSlotCount() const {
    return static_cast<int>(pcie_slots_.size());
}

VRM& Motherboard::GetVRM() {
    return vrm_;
}

const VRM& Motherboard::GetVRM() const {
    return vrm_;
}

Chipset& Motherboard::GetChipset() {
    return chipset_;
}

const Chipset& Motherboard::GetChipset() const {
    return chipset_;
}

PCIeSlot& Motherboard::GetSlot(int index) {
    if (index < 0 || index >= pcie_slots_.size()) 
        throw DeviceNotFoundException("PCIe slot index out of range.");
    return pcie_slots_[index];
}

const PCIeSlot& Motherboard::GetSlot(int index) const {
    if (index < 0 || index >= pcie_slots_.size()) 
        throw DeviceNotFoundException("PCIe slot index out of range.");
    return pcie_slots_[index];
}
