/**
 * @file VRM.cpp
 * @brief Implementation of VRM methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "VRM.h"
#include "Exceptions.h"

VRM::VRM(int phase_count, double vcore_voltage, double temperature_celsius, double efficiency_percentage) :
    phase_count_(phase_count), vcore_voltage_(vcore_voltage), temperature_celsius_(temperature_celsius), efficiency_percentage_(efficiency_percentage) {}

bool VRM::operator==(const VRM& other) const {
    return phase_count_ == other.phase_count_ && vcore_voltage_ == other.vcore_voltage_ &&
           temperature_celsius_ == other.temperature_celsius_ && efficiency_percentage_ == other.efficiency_percentage_;
}

bool VRM::operator!=(const VRM& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const VRM& vrm) {
    os << "VRM (" << vrm.phase_count_ << " phases, " << vrm.vcore_voltage_ << " V, " << vrm.temperature_celsius_ << " C, " << vrm.efficiency_percentage_ << "% efficiency)";
    return os;
}

void VRM::SetVCoreVoltage(double volts) {
    if (volts < 0.5 || volts > 1.85) 
        throw VoltageInstabilityException("VCore voltage out of safe bounds (0.5V - 1.85V).");
    vcore_voltage_ = volts;
}

void VRM::SupplyCurrent(double current_amperes) {
    if (current_amperes < 0.0) 
        return;
    double thermal_delta = current_amperes * (1.0 - efficiency_percentage_ / 100) * 0.8;
    temperature_celsius_ += thermal_delta;
    if (temperature_celsius_ > 115.0) 
        throw OverheatingException("VRM thermal limit exceeded (> 115 °C).");
}

void VRM::CoolDown(double delta_celsius) {
    if (delta_celsius <= 0.0) 
        return;
    temperature_celsius_ -= delta_celsius;
    if (temperature_celsius_ < 25.0) 
        temperature_celsius_ = 25.0;
}

double VRM::CalculatePowerLossWatts(double current_amperes) const {
    if (current_amperes <= 0.0) 
        return 0.0;
    return current_amperes * vcore_voltage_ * (1.0 - efficiency_percentage_ / 100);
}

int VRM::GetPhaseCount() const {
    return phase_count_;
}

double VRM::GetVCoreVoltage() const {
    return vcore_voltage_;
}

double VRM::GetTemperatureCelsius() const {
    return temperature_celsius_;
}

double VRM::GetEfficiencyPercentage() const {
    return efficiency_percentage_;
}
