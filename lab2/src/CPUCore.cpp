/**
 * @file CPUCore.cpp
 * @brief Implementation of CPUCore methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "CPUCore.h"
#include "Exceptions.h"

namespace {
constexpr double kIdleTemperature = 35.0;
constexpr double kSafeBoostThreshold = 85.0;
constexpr double kThrottleThreshold = 95.0;
constexpr double kCriticalOverheatThreshold = 105.0;
}

CPUCore::CPUCore(int core_id, int base_clock_mhz, bool enable_hyperthreading) :
    core_id_(core_id),
      base_clock_mhz_(base_clock_mhz),
      current_clock_mhz_(base_clock_mhz),
      load_percentage_(0.0),
      temperature_celsius_(kIdleTemperature),
      is_hyperthreading_active_(enable_hyperthreading) {}

bool CPUCore::operator==(const CPUCore& other) const {
    return (core_id_ == other.core_id_ &&
            base_clock_mhz_ == other.base_clock_mhz_ &&
            current_clock_mhz_ == other.current_clock_mhz_ &&
            is_hyperthreading_active_ == other.is_hyperthreading_active_);
}

bool CPUCore::operator!=(const CPUCore& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CPUCore& core) {
    os << "Core #" << core.core_id_ << " [" << core.current_clock_mhz_ << " MHz, Load: "
       << core.load_percentage_ << "%, Temp: " << core.temperature_celsius_ << " C]";
    return os;
}

void CPUCore::ExecuteInstructions(long long instruction_count) {
    double added_temp = static_cast<double>(instruction_count) / 1000000.0;
    temperature_celsius_ += added_temp;
    load_percentage_ = 100.0;

    if (temperature_celsius_ > kCriticalOverheatThreshold) {
        throw OverheatingException("CPU Core exceeded critical TJMax threshold");
    }
    if (temperature_celsius_ > kThrottleThreshold) {
        Throttle(0.6);
        throw ThermalThrottlingException("CPU Core throttling due to thermal limits");
    }
}

void CPUCore::UpdateLoad(double load) {
    if (load < 0.0) {
        load_percentage_ = 0.0;
    } else if (load > 100.0) {
        load_percentage_ = 100.0;
    } else {
        load_percentage_ = load;
    }
    double load_factor = load_percentage_ / 100.0;
    current_clock_mhz_ = static_cast<int>(base_clock_mhz_ * (0.8 + 0.4 * load_factor));
}

void CPUCore::CoolDown(double delta_celsius) {
    if (delta_celsius > 0.0) {
        temperature_celsius_ -= delta_celsius;
        if (temperature_celsius_ < kIdleTemperature) {
            temperature_celsius_ = kIdleTemperature;
        }
    }
}

bool CPUCore::BoostClock(int target_mhz) {
    if (temperature_celsius_ < kSafeBoostThreshold && target_mhz >= base_clock_mhz_) {
        current_clock_mhz_ = target_mhz;
        return true;
    }
    return false;
}

void CPUCore::Throttle(double factor) {
    if (factor > 0.0 && factor < 1.0) {
        current_clock_mhz_ = static_cast<int>(current_clock_mhz_ * factor);
    }
}

int CPUCore::GetCoreId() const {
    return core_id_;
}

int CPUCore::GetBaseClockMhz() const {
    return base_clock_mhz_;
}

int CPUCore::GetCurrentClockMhz() const {
    return current_clock_mhz_;
}

double CPUCore::GetLoadPercentage() const {
    return load_percentage_;
}

double CPUCore::GetTemperatureCelsius() const {
    return temperature_celsius_;
}

bool CPUCore::IsHyperthreadingActive() const {
    return is_hyperthreading_active_;
}