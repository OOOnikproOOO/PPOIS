/**
 * @file PCIeSlot.cpp
 * @brief Implementation of PCIeSlot methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PCIeSlot.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

PCIeSlot::PCIeSlot(int slot_index, const std::string& generation, int lane_width, bool is_occupied, const std::string& installed_device_name) :
    slot_index_(slot_index), generation_(generation), lane_width_(lane_width), is_occupied_(is_occupied), installed_device_name_(installed_device_name) {}

bool PCIeSlot::operator==(const PCIeSlot& other) const {
    return slot_index_ == other.slot_index_ && generation_ == other.generation_ &&
           lane_width_ == other.lane_width_ && is_occupied_ == other.is_occupied_ &&
           installed_device_name_ == other.installed_device_name_;
}

bool PCIeSlot::operator!=(const PCIeSlot& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PCIeSlot& slot) {
    os << "PCIe Slot #" << slot.slot_index_ << " (" << slot.generation_ << " x" << slot.lane_width_ << ", " << (slot.is_occupied_ ? "Occupied: " + slot.installed_device_name_ : "Empty") << ")";
    return os;
}

void PCIeSlot::InstallDevice(const std::string& device_name) {
    if (device_name.empty()) 
        throw ComputerException("Device name cannot be empty.");
    if (is_occupied_) 
        throw ComputerException("PCIe slot is already occupied.");
    is_occupied_ = true;
    installed_device_name_ = device_name;
}

void PCIeSlot::RemoveDevice() {
    if (!is_occupied_) 
        throw DeviceNotFoundException("Cannot remove device from an empty PCIe slot.");
    is_occupied_ = false;
    installed_device_name_ = "";
}

double PCIeSlot::CalculateBandwidthGBs() const {
    double per_lane_gbs = 1.969;
    if (generation_.find("5.0") != std::string::npos) 
        per_lane_gbs = 3.938;
    else 
        if (generation_.find("3.0") != std::string::npos) 
            per_lane_gbs = 0.985;
    return per_lane_gbs * lane_width_;
}

int PCIeSlot::GetSlotIndex() const {
    return slot_index_;
}

const std::string& PCIeSlot::GetGeneration() const {
    return generation_;
}

int PCIeSlot::GetLaneWidth() const {
    return lane_width_;
}

bool PCIeSlot::IsOccupied() const {
    return is_occupied_;
}

const std::string& PCIeSlot::GetInstalledDeviceName() const {
    return installed_device_name_;
}
