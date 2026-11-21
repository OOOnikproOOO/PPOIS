/**
 * @file GraphicEqualizer.cpp
 * @brief Implementation of GraphicEqualizer methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "GraphicEqualizer.h"
#include "InvalidEqualizerBandException.h"
#include <cmath>

GraphicEqualizer::GraphicEqualizer(const std::string& preset_name, double preamp_gain_db, bool is_active) :
    preset_name_(preset_name), preamp_gain_db_(preamp_gain_db), is_active_(is_active), bands_() {
    const int kFrequencies[10] = {31, 62, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    for (int i = 0; i < 10; i++)
        bands_.push_back(EqualizerBand(kFrequencies[i], 0.0, 1.41, true));
}

bool GraphicEqualizer::operator==(const GraphicEqualizer& other) const {
    const double kEpsilon = 1e-4;
    return preset_name_ == other.preset_name_ &&
           std::abs(preamp_gain_db_ - other.preamp_gain_db_) < kEpsilon &&
           is_active_ == other.is_active_ &&
           bands_ == other.bands_;
}

bool GraphicEqualizer::operator!=(const GraphicEqualizer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const GraphicEqualizer& eq) {
    os << "Equalizer[" << eq.preset_name_ << ", " << eq.bands_.size() << " bands, " << (eq.is_active_ ? "Active" : "Bypass") << "]";
    return os;
}

void GraphicEqualizer::ApplyPreset(const std::string& preset) {
    preset_name_ = preset;
    if (preset == "Rock") {
        double rock_gains[10] = {4.5, 3.0, 2.0, 0.0, -1.5, -1.0, 1.0, 2.5, 3.5, 4.0};
        for (size_t i = 0; i < bands_.size(); i++)
            bands_[i].SetGain(rock_gains[i]);
    } else if (preset == "Pop") {
        double pop_gains[10] = {-1.5, 0.0, 2.0, 3.5, 3.0, 1.0, -0.5, -1.0, 1.5, 2.0};
        for (size_t i = 0; i < bands_.size(); i++)
            bands_[i].SetGain(pop_gains[i]);
    } else
        ResetAllBands();
}

void GraphicEqualizer::SetBandGain(size_t band_index, double gain) {
    if (band_index >= bands_.size())
        throw InvalidEqualizerBandException("Band index " + std::to_string(band_index) + " out of bounds.");
    
    bands_[band_index].SetGain(gain);
    preset_name_ = "Custom";
}

void GraphicEqualizer::ResetAllBands() {
    for (auto& band : bands_)
        band.Reset();
    
    preset_name_ = "Flat";
}

void GraphicEqualizer::ToggleEqualizer(bool active) {
    is_active_ = active;
}

const EqualizerBand& GraphicEqualizer::GetBand(size_t index) const {
    if (index >= bands_.size())
        throw InvalidEqualizerBandException("Band index out of bounds.");
    
    return bands_[index];
}

size_t GraphicEqualizer::GetBandsCount() const {
    return bands_.size();
}

const std::string& GraphicEqualizer::GetPresetName() const {
    return preset_name_;
}

double GraphicEqualizer::GetPreampGainDb() const {
    return preamp_gain_db_;
}

bool GraphicEqualizer::IsActive() const {
    return is_active_;
}