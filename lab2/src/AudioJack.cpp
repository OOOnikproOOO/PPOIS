/**
 * @file AudioJack.cpp
 * @brief Implementation of AudioJack methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioJack.h"

AudioJack::AudioJack(const std::string& port_type, const std::string& color_code, double impedance_ohms) :
    port_type_(port_type), color_code_(color_code), is_plugged_(false), impedance_ohms_(impedance_ohms) {}

bool AudioJack::operator==(const AudioJack& other) const {
    return (port_type_ == other.port_type_ &&
            color_code_ == other.color_code_ &&
            is_plugged_ == other.is_plugged_ &&
            impedance_ohms_ == other.impedance_ohms_);
}

bool AudioJack::operator!=(const AudioJack& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioJack& jack) {
    os << "AudioJack [" << jack.port_type_ << " (" << jack.color_code_ << "), " << (jack.is_plugged_ ? "Connected" : "Empty") << ", " << jack.impedance_ohms_ << " Ohms]";
    return os;
}

void AudioJack::PlugIn() {
    is_plugged_ = true;
}

void AudioJack::Unplug() {
    is_plugged_ = false;
}

bool AudioJack::VerifyImpedanceMatch(double load_ohms) const {
    if (load_ohms < 4.0 || load_ohms > 600.0)
        return false;
    
    return true;
}

std::string AudioJack::GetPortType() const {
    return port_type_;
}

std::string AudioJack::GetColorCode() const {
    return color_code_;
}

bool AudioJack::IsPlugged() const {
    return is_plugged_;
}

double AudioJack::GetImpedanceOhms() const {
    return impedance_ohms_;
}