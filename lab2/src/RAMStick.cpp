/**
 * @file RAMStick.cpp
 * @brief Implementation of RAMStick methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "RAMStick.h"
#include "Exceptions.h"

RAMStick::RAMStick(const std::string& serial_number, int capacity_mb, int frequency_mhz, const std::string& generation, const RAMTiming& timings) :
    serial_number_(serial_number), capacity_mb_(capacity_mb), frequency_mhz_(frequency_mhz), generation_(generation), timings_(timings), xmp_enabled_(false), used_mb_(0) {}

bool RAMStick::operator==(const RAMStick& other) const {
    return (serial_number_ == other.serial_number_ &&
            capacity_mb_ == other.capacity_mb_ &&
            frequency_mhz_ == other.frequency_mhz_ &&
            generation_ == other.generation_);
}

bool RAMStick::operator!=(const RAMStick& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const RAMStick& stick) {
    os << "RAM: " << stick.generation_ << " " << stick.capacity_mb_ << " MB @" << stick.frequency_mhz_ << " MHz (" << stick.timings_ << ", Used: " << stick.used_mb_ << " MB, S/N: " << stick.serial_number_ << ")";
    return os;
}

bool RAMStick::WriteData(int megabytes) {
    if (megabytes <= 0)
        return false;

    if (used_mb_ + megabytes > capacity_mb_)
        throw MemoryAllocationException("RAM stick exhausted available capacity.");
  
    used_mb_ += megabytes;
    return true;
}

bool RAMStick::ReadData(int megabytes) {
    return (megabytes > 0 && megabytes <= used_mb_);
}

void RAMStick::EnableXMP(int profile_frequency, const RAMTiming& profile_timings) {
    frequency_mhz_ = profile_frequency;
    timings_ = profile_timings;
    xmp_enabled_ = true;
}

bool RAMStick::RunDiagnostics() const {
    return (!serial_number_.empty() && capacity_mb_ > 0 && timings_.ValidateTimings());
}

void RAMStick::ClearMemory() {
    used_mb_ = 0;
}

std::string RAMStick::GetSerialNumber() const {
    return serial_number_;
}

int RAMStick::GetCapacityMb() const {
    return capacity_mb_;
}

int RAMStick::GetFrequencyMhz() const {
    return frequency_mhz_;
}

std::string RAMStick::GetGeneration() const {
    return generation_;
}

const RAMTiming& RAMStick::GetTimings() const {
    return timings_;
}

bool RAMStick::IsXmpEnabled() const {
    return xmp_enabled_;
}

int RAMStick::GetUsedMb() const {
    return used_mb_;
}