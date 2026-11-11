/**
 * @file CoolingFan.cpp
 * @brief Implementation of CoolingFan methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "CoolingFan.h"

CoolingFan::CoolingFan(const std::string& fan_name, int diameter_mm, int rpm, int max_rpm, int pwm_duty_cycle) :
    fan_name_(fan_name), diameter_mm_(diameter_mm), rpm_(rpm), max_rpm_(max_rpm), pwm_duty_cycle_(pwm_duty_cycle) {}

bool CoolingFan::operator==(const CoolingFan& other) const {
    return fan_name_ == other.fan_name_ && diameter_mm_ == other.diameter_mm_ &&
           rpm_ == other.rpm_ && max_rpm_ == other.max_rpm_ && pwm_duty_cycle_ == other.pwm_duty_cycle_;
}

bool CoolingFan::operator!=(const CoolingFan& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CoolingFan& fan) {
    os << "CoolingFan " << fan.fan_name_ << " (" << fan.diameter_mm_ << "mm, " << fan.rpm_ << " / " << fan.max_rpm_ << " RPM, PWM: " << fan.pwm_duty_cycle_ << "%)";
    return os;
}

void CoolingFan::SetPwmDutyCycle(int percent) {
    if (percent < 0) 
        percent = 0;
    if (percent > 100) 
        percent = 100;
    pwm_duty_cycle_ = percent;
    rpm_ = static_cast<int>(max_rpm_ * (percent / 100));
}

double CoolingFan::CalculateAirflowCfm() const {
    if (rpm_ <= 0) 
        return 0.0;
    return (diameter_mm_ / 120.0) * (rpm_ / 2000.0) * 60;
}

double CoolingFan::CalculateNoiseLevelDba() const {
    if (rpm_ <= 0) 
        return 0.0;
    int max_val = max_rpm_ > 0 ? max_rpm_ : 1;
    return 15 + 20 * (static_cast<double>(rpm_) / max_val);
}

const std::string& CoolingFan::GetFanName() const {
    return fan_name_;
}

int CoolingFan::GetDiameterMm() const {
    return diameter_mm_;
}

int CoolingFan::GetRpm() const {
    return rpm_;
}

int CoolingFan::GetMaxRpm() const {
    return max_rpm_;
}

int CoolingFan::GetPwmDutyCycle() const {
    return pwm_duty_cycle_;
}
