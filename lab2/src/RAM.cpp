/**
 * @file RAM.cpp
 * @brief Implementation of RAM methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "RAM.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"
#include "IncompatibleMemoryException.h"
#include "MemoryAllocationException.h"

RAM::RAM(int max_slots) : max_slots_(max_slots), sticks_(), channel_mode_(1), total_allocated_mb_(0) {}

bool RAM::operator==(const RAM& other) const {
    return (max_slots_ == other.max_slots_ &&
            sticks_ == other.sticks_ &&
            channel_mode_ == other.channel_mode_);
}

bool RAM::operator!=(const RAM& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const RAM& ram) {
    os << "RAM Subsystem [" << ram.GetTotalCapacityMb() << " MB Total, " << ram.sticks_.size() << "/" << ram.max_slots_ << " Slots, Channel: " << ram.channel_mode_ << "x, Used: " << ram.total_allocated_mb_ << " MB]";
    return os;
}

void RAM::InstallStick(const RAMStick& stick, int slot_index) {
    if (slot_index < 0 || slot_index >= max_slots_)
        throw ComputerException("Invalid RAM slot index specified.");
  
    if (!sticks_.empty() && sticks_[0].GetGeneration() != stick.GetGeneration())
        throw IncompatibleMemoryException("Cannot mix different DDR generations in the same system.");
  
    sticks_.push_back(stick);
    UpdateChannelMode();
}

RAMStick RAM::RemoveStick(int slot_index) {
    if (slot_index < 0 || slot_index >= sticks_.size())
        throw DeviceNotFoundException("No RAM stick installed in requested slot.");
  
    RAMStick removed = sticks_[slot_index];
    sticks_.erase(sticks_.begin() + slot_index);
    UpdateChannelMode();
    return removed;
}

bool RAM::Allocate(int megabytes) {
    if (megabytes <= 0)
        return false;
  
    int available = GetTotalCapacityMb() - total_allocated_mb_;
    if (megabytes > available)
        throw MemoryAllocationException("Insufficient total system memory to allocate request.");
   
    total_allocated_mb_ += megabytes;
    return true;
}

void RAM::Free(int megabytes) {
    if (megabytes <= 0)
        return;
   
    if (megabytes >= total_allocated_mb_)
        total_allocated_mb_ = 0;
    else
        total_allocated_mb_ -= megabytes;
}

int RAM::GetTotalCapacityMb() const {
    int total = 0;
    for (const auto& stick : sticks_)
        total += stick.GetCapacityMb();
  
    return total;
}

RAMStick RAM::GetStick(int slot_index) const {
    if (slot_index < 0 || slot_index >= sticks_.size())
        throw DeviceNotFoundException("No RAM stick found at requested slot index.");
   
    return sticks_[slot_index];
}

int RAM::GetMaxSlots() const {
    return max_slots_;
}

int RAM::GetInstalledSticksCount() const {
    return static_cast<int>(sticks_.size());
}

int RAM::GetChannelMode() const {
    return channel_mode_;
}

int RAM::GetTotalAllocatedMb() const {
    return total_allocated_mb_;
}

void RAM::UpdateChannelMode() {
    int count = static_cast<int>(sticks_.size());
    if (count >= 4)
        channel_mode_ = 4;
    else 
        if (count >= 2)
            channel_mode_ = 2;
        else
            channel_mode_ = 1;
}