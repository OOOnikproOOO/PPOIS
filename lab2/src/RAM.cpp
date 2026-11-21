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

RAM::RAM(int max_slots) : max_slots_(max_slots), sticks_(max_slots, RAMStick("", 0, 0, "", RAMTiming())), channel_mode_(1), total_allocated_mb_(0) {}

bool RAM::operator==(const RAM& other) const {
    if (max_slots_ != other.max_slots_ || channel_mode_ != other.channel_mode_)
        return false;
    for (int i = 0; i < max_slots_; ++i) {
        if (sticks_[i] != other.sticks_[i])
            return false;
    }
    return true;
}

bool RAM::operator!=(const RAM& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const RAM& ram) {
    os << "RAM Subsystem [" << ram.GetTotalCapacityMb() << " MB Total, " << ram.GetInstalledSticksCount() << "/" << ram.max_slots_ << " Slots, Channel: " << ram.channel_mode_ << "x, Used: " << ram.total_allocated_mb_ << " MB]";
    return os;
}

void RAM::InstallStick(const RAMStick& stick, int slot_index) {
    if (slot_index < 0 || slot_index >= max_slots_)
        throw ComputerException("Invalid RAM slot index specified.");
  
    for (const auto& s : sticks_) {
        if (s.GetCapacityMb() > 0 && s.GetGeneration() != stick.GetGeneration())
            throw IncompatibleMemoryException("Cannot mix different DDR generations in the same system.");
    }
  
    sticks_[slot_index] = stick;
    UpdateChannelMode();
}

RAMStick RAM::RemoveStick(int slot_index) {
    if (slot_index < 0 || slot_index >= max_slots_ || sticks_[slot_index].GetCapacityMb() == 0)
        throw DeviceNotFoundException("No RAM stick installed in requested slot.");
  
    RAMStick removed = sticks_[slot_index];
    sticks_[slot_index] = RAMStick("", 0, 0, "", RAMTiming());
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
    for (const auto& stick : sticks_) {
        if (stick.GetCapacityMb() > 0)
            total += stick.GetCapacityMb();
    }
    return total;
}

RAMStick RAM::GetStick(int slot_index) const {
    if (slot_index < 0 || slot_index >= max_slots_ || sticks_[slot_index].GetCapacityMb() == 0)
        throw DeviceNotFoundException("No RAM stick found at requested slot index.");
   
    return sticks_[slot_index];
}

RAMStick& RAM::GetStick(int slot_index) {
    if (slot_index < 0 || slot_index >= max_slots_ || sticks_[slot_index].GetCapacityMb() == 0)
        throw DeviceNotFoundException("No RAM stick found at requested slot index.");
   
    return sticks_[slot_index];
}

int RAM::GetMaxSlots() const {
    return max_slots_;
}

int RAM::GetInstalledSticksCount() const {
    int count = 0;
    for (const auto& stick : sticks_) {
        if (stick.GetCapacityMb() > 0)
            count++;
    }
    return count;
}

int RAM::GetChannelMode() const {
    return channel_mode_;
}

int RAM::GetTotalAllocatedMb() const {
    return total_allocated_mb_;
}

void RAM::UpdateChannelMode() {
    int count = GetInstalledSticksCount();
    if (count >= 4)
        channel_mode_ = 4;
    else if (count >= 2)
        channel_mode_ = 2;
    else
        channel_mode_ = 1;
}