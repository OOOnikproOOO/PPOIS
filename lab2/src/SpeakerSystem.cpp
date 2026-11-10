/**
 * @file SpeakerSystem.cpp
 * @brief Implementation of SpeakerSystem methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SpeakerSystem.h"
#include "Exceptions.h"

SpeakerSystem::SpeakerSystem(const std::string& system_name, int power_watts_rms, int initial_volume) :
    system_name_(system_name), power_watts_rms_(power_watts_rms), current_volume_(initial_volume), is_muted_(false) {}

bool SpeakerSystem::operator==(const SpeakerSystem& other) const {
    return (system_name_ == other.system_name_ &&
            power_watts_rms_ == other.power_watts_rms_ &&
            current_volume_ == other.current_volume_ &&
            is_muted_ == other.is_muted_);
}

bool SpeakerSystem::operator!=(const SpeakerSystem& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SpeakerSystem& speaker) {
    os << "SpeakerSystem: " << speaker.system_name_ << " [" << speaker.power_watts_rms_ << " W RMS, Vol: " << speaker.current_volume_ << "%, " << (speaker.is_muted_ ? "Muted" : "Active") << "]";
    return os;
}

void SpeakerSystem::SetVolume(int volume) {
    if (volume < 0 || volume > 100)
        throw ComputerException("Speaker volume must be between 0 and 100%.");
    
    current_volume_ = volume;
    if (current_volume_ > 0)
        is_muted_ = false;
}

void SpeakerSystem::ToggleMute() {
    is_muted_ = !is_muted_;
}

bool SpeakerSystem::OutputSound(int duration_seconds, double db_level) {
    if (is_muted_ || current_volume_ == 0)
        return false;
   
    if (duration_seconds <= 0)
        return false;
    
    if (db_level > 120)
        throw ComputerException("Acoustic output level exceeds safe hearing limits (120 dB SPL).");
    
    return true;
}

std::string SpeakerSystem::GetSystemName() const {
    return system_name_;
}

int SpeakerSystem::GetPowerWattsRms() const {
    return power_watts_rms_;
}

int SpeakerSystem::GetCurrentVolume() const {
    return current_volume_;
}

bool SpeakerSystem::IsMuted() const {
    return is_muted_;
}