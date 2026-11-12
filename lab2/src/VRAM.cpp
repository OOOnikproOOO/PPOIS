/**
 * @file VRAM.cpp
 * @brief Implementation of VRAM methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "VRAM.h"
#include "MemoryAllocationException.h"

VRAM::VRAM(int capacity_mb, int bus_width_bits, const std::string& memory_type) :
    capacity_mb_(capacity_mb), bus_width_bits_(bus_width_bits), used_mb_(0), memory_type_(memory_type) {}

bool VRAM::operator==(const VRAM& other) const {
    return (capacity_mb_ == other.capacity_mb_ &&
            bus_width_bits_ == other.bus_width_bits_ &&
            memory_type_ == other.memory_type_);
}

bool VRAM::operator!=(const VRAM& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const VRAM& vram) {
    os << "VRAM: " << vram.capacity_mb_ << " MB " << vram.memory_type_ << " [" << vram.bus_width_bits_ << "-bit, Used: " << vram.used_mb_ << " MB]";
    return os;
}

bool VRAM::Allocate(int megabytes) {
    if (megabytes <= 0)
        return false;
    
    int available = capacity_mb_ - used_mb_;
    if (megabytes > available)
        throw MemoryAllocationException("VRAM out of memory: insufficient space for texture buffers.");
    
    used_mb_ += megabytes;
    return true;
}

void VRAM::Free(int megabytes) {
    if (megabytes <= 0)
        return;
    
    if (megabytes >= used_mb_)
        used_mb_ = 0;
    else
        used_mb_ -= megabytes;
}

double VRAM::CalculateBandwidthGbps(int memory_clock_mhz) const {
    if (memory_clock_mhz <= 0)
        return 0.0;
  
    double bytes_per_cycle = bus_width_bits_ / 8.0;
    double transfers_per_sec = memory_clock_mhz * 2.0;
    return (bytes_per_cycle * transfers_per_sec) / 1000;
}

int VRAM::GetCapacityMb() const {
    return capacity_mb_;
}

int VRAM::GetBusWidthBits() const {
    return bus_width_bits_;
}

int VRAM::GetUsedMb() const {
    return used_mb_;
}

std::string VRAM::GetMemoryType() const {
    return memory_type_;
}