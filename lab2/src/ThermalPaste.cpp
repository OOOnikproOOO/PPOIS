/**
 * @file ThermalPaste.cpp
 * @brief Implementation of ThermalPaste methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ThermalPaste.h"

ThermalPaste::ThermalPaste(const std::string& brand_name, double thermal_conductivity, double viscosity, double thickness_mm) :
    brand_name_(brand_name), thermal_conductivity_(thermal_conductivity), viscosity_(viscosity), thickness_mm_(thickness_mm), service_years_(0.0), is_dry_(false) {}

bool ThermalPaste::operator==(const ThermalPaste& other) const {
    return (brand_name_ == other.brand_name_ &&
            thermal_conductivity_ == other.thermal_conductivity_ &&
            thickness_mm_ == other.thickness_mm_);
}

bool ThermalPaste::operator!=(const ThermalPaste& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const ThermalPaste& paste) {
    os << "Thermal Paste: " << paste.brand_name_ << " [" << paste.thermal_conductivity_ << " W/(m*K), " << paste.thickness_mm_ << " mm, Age: " << paste.service_years_ << " yrs, Dry: " << (paste.is_dry_ ? "Yes" : "No") << "]";
    return os;
}

double ThermalPaste::CalculateThermalResistance(double surface_area_cm2) const {
    if (surface_area_cm2 <= 0.0 || thermal_conductivity_ <= 0.0)
        return 1.0;
    
    double area_m2 = surface_area_cm2 / 10000;
    double thickness_m = thickness_mm_ / 1000;
    return thickness_m / (thermal_conductivity_ * area_m2);
}

void ThermalPaste::DegradeOverTime(double years) {
    if (years <= 0.0)
        return;
    
    service_years_ += years;
    if (service_years_ >= 3.0) {
        is_dry_ = true;
        thermal_conductivity_ = std::max(1.0, thermal_conductivity_ * 0.5);
    }
}

void ThermalPaste::ReplacePaste(double new_conductivity, double new_thickness) {
    thermal_conductivity_ = new_conductivity;
    thickness_mm_ = new_thickness;
    service_years_ = 0;
    is_dry_ = false;
}

bool ThermalPaste::IsEffective() const {
    return (!is_dry_ && thermal_conductivity_ >= 3.0);
}

double ThermalPaste::EvaluateHeatTransferEfficiency() const {
    if (is_dry_)
        return 0.2;
    
    double score = thermal_conductivity_ / 12;
    if (score > 1.0)
        score = 1.0;
    
    return score;
}

std::string ThermalPaste::GetBrandName() const {
    return brand_name_;
}

double ThermalPaste::GetThermalConductivity() const {
    return thermal_conductivity_;
}

double ThermalPaste::GetViscosity() const {
    return viscosity_;
}

double ThermalPaste::GetThicknessMm() const {
    return thickness_mm_;
}

double ThermalPaste::GetServiceYears() const {
    return service_years_;
}

bool ThermalPaste::IsDry() const {
    return is_dry_;
}