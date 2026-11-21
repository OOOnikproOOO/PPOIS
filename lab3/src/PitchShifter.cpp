/**
 * @file PitchShifter.cpp
 * @brief Implementation of PitchShifter methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PitchShifter.h"
#include <cmath>

PitchShifter::PitchShifter(int semitones_offset, double tempo_multiplier, const std::string& quality_mode, bool is_active) :
    semitones_offset_(semitones_offset > 12 ? 12 : (semitones_offset < -12 ? -12 : semitones_offset)), tempo_multiplier_(tempo_multiplier > 2.0 ? 2.0 : (tempo_multiplier < 0.5 ? 0.5 : tempo_multiplier)), quality_mode_(quality_mode), is_active_(is_active) {}

bool PitchShifter::operator==(const PitchShifter& other) const {
    const double kEpsilon = 1e-4;
    return semitones_offset_ == other.semitones_offset_ &&
           std::abs(tempo_multiplier_ - other.tempo_multiplier_) < kEpsilon &&
           quality_mode_ == other.quality_mode_ &&
           is_active_ == other.is_active_;
}

bool PitchShifter::operator!=(const PitchShifter& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PitchShifter& ps) {
    os << "PitchShifter[" << (ps.semitones_offset_ >= 0 ? "+" : "") << ps.semitones_offset_ << " semitones, " << ps.tempo_multiplier_ << "x speed (" << (ps.is_active_ ? "ON" : "OFF") << ")]";
    return os;
}

void PitchShifter::SetPitchOffset(int semitones) {
    if (semitones < -12)
        semitones = -12;
    
    if (semitones > 12)
        semitones = 12;
    
    semitones_offset_ = semitones;
    is_active_ = (semitones_offset_ != 0 || std::abs(tempo_multiplier_ - 1.0) > 1e-4);
}

void PitchShifter::SetTempo(double tempo) {
    if (tempo < 0.5)
        tempo = 0.5;
    
    if (tempo > 2.0)
        tempo = 2.0;
    
    tempo_multiplier_ = tempo;
    is_active_ = (semitones_offset_ != 0 || std::abs(tempo_multiplier_ - 1.0) > 1e-4);
}

double PitchShifter::CalculateFrequencyMultiplier() const {
    return std::pow(2.0, static_cast<double>(semitones_offset_) / 12);
}

void PitchShifter::ResetPitch() {
    semitones_offset_ = 0;
    tempo_multiplier_ = 1.0;
    is_active_ = false;
}

int PitchShifter::GetSemitonesOffset() const {
    return semitones_offset_;
}

double PitchShifter::GetTempoMultiplier() const {
    return tempo_multiplier_;
}

const std::string& PitchShifter::GetQualityMode() const {
    return quality_mode_;
}

bool PitchShifter::IsActive() const {
    return is_active_;
}