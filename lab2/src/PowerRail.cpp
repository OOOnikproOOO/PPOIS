/**
 * @file PowerRail.cpp
 * @brief Implementation of PowerRail methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PowerRail.h"
#include "PowerSupplyOverloadException.h"

PowerRail::PowerRail(const std::string& rail_name, double nominal_voltage, double current_amperes, double max_amperes) :
    rail_name_(rail_name), nominal_voltage_(nominal_voltage), current_amperes_(current_amperes), max_amperes_(max_amperes) {}

bool PowerRail::operator==(const PowerRail& other) const {
    return rail_name_ == other.rail_name_ && nominal_voltage_ == other.nominal_voltage_ &&
           current_amperes_ == other.current_amperes_ && max_amperes_ == other.max_amperes_;
}

bool PowerRail::operator!=(const PowerRail& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PowerRail& rail) {
    os << "PowerRail " << rail.rail_name_ << " (" << rail.nominal_voltage_ << " V, " << rail.current_amperes_ << " A / " << rail.max_amperes_ << " A max)";
    return os;
}

void PowerRail::DrawCurrent(double amperes) {
    if (amperes <= 0.0) 
        return;
    current_amperes_ += amperes;
    if (current_amperes_ > max_amperes_) 
        throw PowerSupplyOverloadException("Power rail overload detected on " + rail_name_ + ".");
}

void PowerRail::ReleaseCurrent(double amperes) {
    if (amperes <= 0.0) 
        return;
    current_amperes_ -= amperes;
    if (current_amperes_ < 0.0) 
        current_amperes_ = 0.0;
}

double PowerRail::CalculateCurrentPowerWatts() const {
    return nominal_voltage_ * current_amperes_;
}

const std::string& PowerRail::GetRailName() const {
    return rail_name_;
}

double PowerRail::GetNominalVoltage() const {
    return nominal_voltage_;
}

double PowerRail::GetCurrentAmperes() const {
    return current_amperes_;
}

double PowerRail::GetMaxAmperes() const {
    return max_amperes_;
}
