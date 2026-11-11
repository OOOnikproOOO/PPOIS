/**
 * @file LiquidCooler.cpp
 * @brief Implementation of LiquidCooler methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "LiquidCooler.h"
#include "Exceptions.h"

LiquidCooler::LiquidCooler(const std::string& model_name, int radiator_size_mm, int pump_rpm, double coolant_temperature_celsius, double flow_rate_lph) :
    model_name_(model_name), radiator_size_mm_(radiator_size_mm), pump_rpm_(pump_rpm), coolant_temperature_celsius_(coolant_temperature_celsius), flow_rate_lph_(flow_rate_lph) {}

bool LiquidCooler::operator==(const LiquidCooler& other) const {
    return model_name_ == other.model_name_ && radiator_size_mm_ == other.radiator_size_mm_ &&
           pump_rpm_ == other.pump_rpm_ && coolant_temperature_celsius_ == other.coolant_temperature_celsius_ &&
           flow_rate_lph_ == other.flow_rate_lph_;
}

bool LiquidCooler::operator!=(const LiquidCooler& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const LiquidCooler& cooler) {
    os << "LiquidCooler " << cooler.model_name_ << " (" << cooler.radiator_size_mm_ << "mm radiator, " << cooler.pump_rpm_ << " RPM, " << cooler.coolant_temperature_celsius_ << " C, " << cooler.flow_rate_lph_ << " L/h)";
    return os;
}

void LiquidCooler::SetPumpSpeed(int target_rpm) {
    if (target_rpm < 800) 
        throw ComputerException("Pump speed too low to maintain flow (< 800 RPM).");
    pump_rpm_ = target_rpm;
    flow_rate_lph_ = 150 * (static_cast<double>(target_rpm) / 2800);
}

void LiquidCooler::AbsorbHeat(double heat_watts) {
    if (heat_watts <= 0.0) 
        return;
    coolant_temperature_celsius_ += heat_watts * 0.04;
    if (coolant_temperature_celsius_ > 65.0) 
        throw OverheatingException("Coolant temperature critical (> 65 °C). AIO loop failure.");
}

void LiquidCooler::DissipateHeat(double delta_celsius) {
    if (delta_celsius <= 0.0) 
        return;
    coolant_temperature_celsius_ -= delta_celsius;
    if (coolant_temperature_celsius_ < 22.0) 
        coolant_temperature_celsius_ = 22.0;
}

const std::string& LiquidCooler::GetModelName() const {
    return model_name_;
}

int LiquidCooler::GetRadiatorSizeMm() const {
    return radiator_size_mm_;
}

int LiquidCooler::GetPumpRpm() const {
    return pump_rpm_;
}

double LiquidCooler::GetCoolantTemperatureCelsius() const {
    return coolant_temperature_celsius_;
}

double LiquidCooler::GetFlowRateLph() const {
    return flow_rate_lph_;
}
