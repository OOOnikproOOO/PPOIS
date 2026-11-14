/**
 * @file SystemDiagnostics.cpp
 * @brief Implementation of SystemDiagnostics methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SystemDiagnostics.h"
#include "ThermalThrottlingException.h"
#include "PowerSupplyOverloadException.h"

SystemDiagnostics::SystemDiagnostics(bool all_systems_nominal, int warnings_count, double max_recorded_temp, double total_power_draw) :
    all_systems_nominal_(all_systems_nominal), warnings_count_(warnings_count), max_recorded_temp_(max_recorded_temp), total_power_draw_(total_power_draw) {}

bool SystemDiagnostics::operator==(const SystemDiagnostics& other) const {
    return all_systems_nominal_ == other.all_systems_nominal_ &&
           warnings_count_ == other.warnings_count_ &&
           max_recorded_temp_ == other.max_recorded_temp_ &&
           total_power_draw_ == other.total_power_draw_;
}

bool SystemDiagnostics::operator!=(const SystemDiagnostics& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SystemDiagnostics& diag) {
    os << "Diagnostics [" << (diag.all_systems_nominal_ ? "NOMINAL" : "WARNING") << ", Incidents: " << diag.warnings_count_ << ", Peak Temp: " << diag.max_recorded_temp_ << " C, Power: " << diag.total_power_draw_ << " W]";
    return os;
}

bool SystemDiagnostics::DiagnoseTemperatures(double cpu_temp, double gpu_temp, double vrm_temp) {
    double peak = cpu_temp;
    if (gpu_temp > peak) 
        peak = gpu_temp;
    if (vrm_temp > peak) 
        peak = vrm_temp;
    if (peak > max_recorded_temp_) 
        max_recorded_temp_ = peak;

    if (peak > 95.0) {
        all_systems_nominal_ = false;
        warnings_count_++;
        throw ThermalThrottlingException("Diagnostics alert: Component temperature exceeds safety limit (> 95 °C).");
    }
    all_systems_nominal_ = true;
    return true;
}

bool SystemDiagnostics::DiagnosePower(int power_draw_w, int rated_w) {
    total_power_draw_ = power_draw_w;
    if (power_draw_w > rated_w) {
        all_systems_nominal_ = false;
        warnings_count_++;
        throw PowerSupplyOverloadException("Diagnostics alert: System power draw exceeds PSU capacity.");
    }
    return true;
}

void SystemDiagnostics::ResetDiagnostics() {
    all_systems_nominal_ = true;
    warnings_count_ = 0;
}

void SystemDiagnostics::RecordIncident() {
    warnings_count_++;
    all_systems_nominal_ = false;
}

bool SystemDiagnostics::IsNominal() const {
    return all_systems_nominal_;
}

int SystemDiagnostics::GetWarningsCount() const {
    return warnings_count_;
}

double SystemDiagnostics::GetMaxRecordedTemp() const {
    return max_recorded_temp_;
}

double SystemDiagnostics::GetTotalPowerDraw() const {
    return total_power_draw_;
}