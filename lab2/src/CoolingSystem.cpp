/**
 * @file CoolingSystem.cpp
 * @brief Implementation of CoolingSystem methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "CoolingSystem.h"
#include "Exceptions.h"

CoolingSystem::CoolingSystem(const std::string& fan_profile, double target_temperature_celsius, const LiquidCooler& liquid_cooler) :
    fan_profile_(fan_profile), target_temperature_celsius_(target_temperature_celsius), liquid_cooler_(liquid_cooler) {}

bool CoolingSystem::operator==(const CoolingSystem& other) const {
    return fan_profile_ == other.fan_profile_ && target_temperature_celsius_ == other.target_temperature_celsius_ &&
           liquid_cooler_ == other.liquid_cooler_;
}

bool CoolingSystem::operator!=(const CoolingSystem& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CoolingSystem& cooling) {
    os << "CoolingSystem [Profile: '" << cooling.fan_profile_ << "', Target: " << cooling.target_temperature_celsius_ << " C, Fans: " << cooling.fans_.size() << ", " << cooling.liquid_cooler_ << "]";
    return os;
}

void CoolingSystem::AddFan(const CoolingFan& fan) {
    fans_.push_back(fan);
}

void CoolingSystem::ApplyProfile(const std::string& profile) {
    int pwm = 50;
    int pump = 2200;
    if (profile == "Silent") {
        pwm = 30;
        pump = 1600;
    } else if (profile == "Standard") {
        pwm = 50;
        pump = 2200;
    } else if (profile == "Performance") {
        pwm = 75;
        pump = 2600;
    } else if (profile == "Full Speed") {
        pwm = 100;
        pump = 2800;
    } else
        throw ComputerException("Unknown fan profile preset: '" + profile + "'.");

    fan_profile_ = profile;
    for (int i = 0; i < fans_.size(); i++)
        fans_[i].SetPwmDutyCycle(pwm);
    
    liquid_cooler_.SetPumpSpeed(pump);
}

double CoolingSystem::CalculateTotalAirflowCfm() const {
    double total = 0.0;
    for (int i = 0; i < fans_.size(); i++)
        total += fans_[i].CalculateAirflowCfm();
    
    return total;
}

const std::string& CoolingSystem::GetFanProfile() const {
    return fan_profile_;
}

double CoolingSystem::GetTargetTemperatureCelsius() const {
    return target_temperature_celsius_;
}

int CoolingSystem::GetFanCount() const {
    return static_cast<int>(fans_.size());
}

LiquidCooler& CoolingSystem::GetLiquidCooler() {
    return liquid_cooler_;
}

const LiquidCooler& CoolingSystem::GetLiquidCooler() const {
    return liquid_cooler_;
}

CoolingFan& CoolingSystem::GetFan(int index) {
    if (index < 0 || index >= fans_.size()) 
        throw DeviceNotFoundException("Cooling fan index out of range.");
    return fans_[index];
}

const CoolingFan& CoolingSystem::GetFan(int index) const {
    if (index < 0 || index >= fans_.size()) 
        throw DeviceNotFoundException("Cooling fan index out of range.");
    return fans_[index];
}
