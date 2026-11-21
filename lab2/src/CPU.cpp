/**
 * @file CPU.cpp
 * @brief Implementation of CPU methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "CPU.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

CPU::CPU(const std::string& model_name, const std::string& socket_type, int tdp_watts, int l3_cache_size_kb) : 
    model_name_(model_name), socket_type_(socket_type), tdp_watts_(tdp_watts), cores_(), l3_cache_(3, l3_cache_size_kb, 64), is_overclocked_(false) {}

bool CPU::operator==(const CPU& other) const {
    return (model_name_ == other.model_name_ &&
            socket_type_ == other.socket_type_ &&
            tdp_watts_ == other.tdp_watts_);
}

bool CPU::operator!=(const CPU& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CPU& cpu) {
    os << "CPU: " << cpu.model_name_ << " [" << cpu.socket_type_ << ", TDP: " << cpu.tdp_watts_ << " W, Cores: " << cpu.cores_.size() << "]";
    return os;
}

void CPU::AddCore(const CPUCore& core) {
    cores_.push_back(core);
}

void CPU::ComputeWorkload(long long total_instructions) {
    if (cores_.empty())
        throw DeviceNotFoundException("CPU has no installed cores to execute instructions.");

    long long per_core = total_instructions / static_cast<long long>(cores_.size());
    for (auto& core : cores_)
        core.ExecuteInstructions(per_core);
}

void CPU::Overclock(double multiplier) {
    if (multiplier <= 1.0 || multiplier > 1.8) {
        throw ComputerException("Invalid CPU overclock multiplier specified.");
    }
    for (auto& core : cores_) {
        int boosted = static_cast<int>(core.GetBaseClockMhz() * multiplier);
        core.BoostClock(boosted);
    }
    is_overclocked_ = true;
}

double CPU::GetAverageTemperature() const {
    if (cores_.empty())
        return 25.0;

    double total_temp = 0.0;
    for (const auto& core : cores_)
        total_temp += core.GetTemperatureCelsius();

    return total_temp / static_cast<double>(cores_.size());
}

int CPU::CalculateCurrentPowerDraw() const {
    if (cores_.empty())
        return 10;

    double total_load = 0.0;
    for (const auto& core : cores_)
        total_load += core.GetLoadPercentage();
 
    double avg_load = total_load / static_cast<double>(cores_.size());
    double overclock_factor = is_overclocked_ ? 1.3 : 1.0;

    return static_cast<int>(tdp_watts_ * (0.2 + 0.8 * (avg_load / 100.0)) * overclock_factor);
}

std::string CPU::GetModelName() const {
    return model_name_;
}

std::string CPU::GetSocketType() const {
    return socket_type_;
}

int CPU::GetTdpWatts() const {
    return tdp_watts_;
}

void CPU::CoolDown(double delta_celsius) {
    for (auto& core : cores_)
        core.CoolDown(delta_celsius);
}

int CPU::GetCoreCount() const {
    return static_cast<int>(cores_.size());
}

CPUCore& CPU::GetCore(int index) {
    if (index < 0 || index >= static_cast<int>(cores_.size()))
        throw DeviceNotFoundException("CPU core index out of range.");

    return cores_[index];
}

const CPUCore& CPU::GetCore(int index) const {
    if (index < 0 || index >= static_cast<int>(cores_.size()))
        throw DeviceNotFoundException("CPU core index out of range.");

    return cores_[index];
}

CPUCache& CPU::GetL3Cache() {
    return l3_cache_;
}

const CPUCache& CPU::GetL3Cache() const {
    return l3_cache_;
}

bool CPU::IsOverclocked() const {
    return is_overclocked_;
}