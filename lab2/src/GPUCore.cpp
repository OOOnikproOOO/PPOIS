/**
 * @file GPUCore.cpp
 * @brief Implementation of the GPUCore methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "GPUCore.h"
#include "ComputerException.h"
#include "ThermalThrottlingException.h"
#include "OverheatingException.h"

GPUCore::GPUCore(int core_id, int clock_mhz) : core_id_(core_id), clock_mhz_(clock_mhz), temperature_celsius_(38.0), load_percentage_(0.0) {}

bool GPUCore::operator==(const GPUCore& other) const {
    return (core_id_ == other.core_id_ && clock_mhz_ == other.clock_mhz_);
}

bool GPUCore::operator!=(const GPUCore& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const GPUCore& core) {
    os << "GPU Core #" << core.core_id_ << " [" << core.clock_mhz_ << " MHz, " << core.temperature_celsius_ << " C, Load: " << core.load_percentage_ << "%]";
    return os;
}

void GPUCore::RenderFrames(int frame_count) {
    if (frame_count <= 0)
        return;
    
    double load_increment = frame_count * 0.2;
    load_percentage_ = std::min(100.0, load_percentage_ + load_increment);
    temperature_celsius_ += frame_count * 0.08;

    if (temperature_celsius_ > 95.0)
        throw OverheatingException("GPU Core temperature exceeded critical junction limit (95 В°C).");
    
    if (temperature_celsius_ > 83.0)
        throw ThermalThrottlingException("GPU Core thermal throttling engaged due to high heat.");
}

void GPUCore::CoolDown(double delta_celsius) {
    if (delta_celsius <= 0.0)
        return;
    
    temperature_celsius_ = std::max(25.0, temperature_celsius_ - delta_celsius);
    load_percentage_ = std::max(0.0, load_percentage_ - 15.0);
}

void GPUCore::SetClockMhz(int new_clock) {
    if (new_clock < 500 || new_clock > 4000)
        throw ComputerException("Invalid GPU core frequency: outside safe boundaries (500 - 4000 MHz).");
    
    if (temperature_celsius_ > 85.0 && new_clock > clock_mhz_)
        throw OverheatingException("Cannot overclock GPU core while thermal threshold is exceeded.");
    
    clock_mhz_ = new_clock;
}

int GPUCore::GetCoreId() const {
    return core_id_;
}

int GPUCore::GetClockMhz() const {
    return clock_mhz_;
}

double GPUCore::GetTemperatureCelsius() const {
    return temperature_celsius_;
}

double GPUCore::GetLoadPercentage() const {
    return load_percentage_;
}