/**
 * @file PowerSupply.cpp
 * @brief Implementation of PowerSupply methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PowerSupply.h"
#include "DeviceNotFoundException.h"
#include "PowerSupplyOverloadException.h"

PowerSupply::PowerSupply(const std::string& model_name, int rated_wattage, const std::string& efficiency_rating, bool is_powered_on) :
    model_name_(model_name), rated_wattage_(rated_wattage), efficiency_rating_(efficiency_rating), is_powered_on_(is_powered_on) {}

bool PowerSupply::operator==(const PowerSupply& other) const {
    return model_name_ == other.model_name_ && rated_wattage_ == other.rated_wattage_ &&
           efficiency_rating_ == other.efficiency_rating_ && is_powered_on_ == other.is_powered_on_;
}

bool PowerSupply::operator!=(const PowerSupply& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PowerSupply& psu) {
    os << "PowerSupply " << psu.model_name_ << " (" << psu.rated_wattage_ << " W, " << psu.efficiency_rating_ << ", " << (psu.is_powered_on_ ? "Power: ON" : "Power: OFF") << ")";
    return os;
}

void PowerSupply::AddRail(const PowerRail& rail) {
    rails_.push_back(rail);
}

void PowerSupply::PowerOn() {
    is_powered_on_ = true;
}

void PowerSupply::PowerOff() {
    is_powered_on_ = false;
}

int PowerSupply::CalculateTotalPowerDrawWatts() const {
    double total_watts = 0.0;
    for (int i = 0; i < rails_.size(); i++)
        total_watts += rails_[i].CalculateCurrentPowerWatts();
    
    int total = static_cast<int>(total_watts);
    if (total > rated_wattage_) 
        throw PowerSupplyOverloadException("Total power draw exceeds power supply capacity (" + std::to_string(total) + " W > " + std::to_string(rated_wattage_) + " W).");
    return total;
}

double PowerSupply::CalculateEfficiencyAtLoad(int load_watts) const {
    if (load_watts <= 0 || rated_wattage_ <= 0) 
        return 0.0;
    double load_ratio = static_cast<double>(load_watts) / rated_wattage_;
    double base_eff = 0.88;
    if (efficiency_rating_.find("Platinum") != std::string::npos) 
        base_eff = 0.92;
    else 
        if (efficiency_rating_.find("Gold") != std::string::npos) 
            base_eff = 0.90;
        else 
            if (efficiency_rating_.find("Bronze") != std::string::npos) 
                base_eff = 0.85;

    if (load_ratio >= 0.4 && load_ratio <= 0.6) 
        return base_eff;
    return base_eff - 0.03;
}

const std::string& PowerSupply::GetModelName() const {
    return model_name_;
}

int PowerSupply::GetRatedWattage() const {
    return rated_wattage_;
}

const std::string& PowerSupply::GetEfficiencyRating() const {
    return efficiency_rating_;
}

bool PowerSupply::IsPoweredOn() const {
    return is_powered_on_;
}

int PowerSupply::GetRailCount() const {
    return static_cast<int>(rails_.size());
}

PowerRail& PowerSupply::GetRail(int index) {
    if (index < 0 || index >= rails_.size()) 
        throw DeviceNotFoundException("Power rail index out of range.");
    return rails_[index];
}

const PowerRail& PowerSupply::GetRail(int index) const {
    if (index < 0 || index >= rails_.size()) 
        throw DeviceNotFoundException("Power rail index out of range.");
    return rails_[index];
}
