/**
 * @file SpectrumAnalyzer.cpp
 * @brief Implementation of SpectrumAnalyzer methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SpectrumAnalyzer.h"
#include <cmath>
#include <numeric>

SpectrumAnalyzer::SpectrumAnalyzer(size_t bands_count, double peak_decay_rate, bool is_active) :
    bands_count_(bands_count < 4 ? 4 : (bands_count > 64 ? 64 : bands_count)), peak_decay_rate_(peak_decay_rate < 0.01 ? 0.01 : (peak_decay_rate > 0.5 ? 0.5 : peak_decay_rate)), is_active_(is_active), band_energies_(bands_count_, 0.0) {}

bool SpectrumAnalyzer::operator==(const SpectrumAnalyzer& other) const {
    const double kEpsilon = 1e-4;
    return bands_count_ == other.bands_count_ &&
           std::abs(peak_decay_rate_ - other.peak_decay_rate_) < kEpsilon &&
           is_active_ == other.is_active_;
}

bool SpectrumAnalyzer::operator!=(const SpectrumAnalyzer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SpectrumAnalyzer& analyzer) {
    os << "SpectrumAnalyzer[" << analyzer.bands_count_ << " bands, Total Energy: " << analyzer.CalculateTotalEnergy() << "]";
    return os;
}

void SpectrumAnalyzer::ProcessBuffer(const AudioBuffer& buffer) {
    if (!is_active_)
        return;

    size_t sample_count = buffer.GetAvailableSamplesCount();
    if (sample_count == 0) {
        for (size_t i = 0; i < bands_count_; i++) {
            band_energies_[i] -= peak_decay_rate_;
            if (band_energies_[i] < 0.0)
                band_energies_[i] = 0.0;
        }

        return;
    }

    double occupancy = buffer.GetOccupancyPercentage() / 100;
    for (size_t i = 0; i < bands_count_; i++) {
        double weight = 1 - (static_cast<double>(i) / (bands_count_ * 1.5));
        double target = occupancy * weight;
        if (target > band_energies_[i])
            band_energies_[i] = target;
        else {
            band_energies_[i] -= peak_decay_rate_;
            if (band_energies_[i] < 0.0)
                band_energies_[i] = 0.0;
        }
    }
}

double SpectrumAnalyzer::GetBandEnergy(size_t band_index) const {
    if (band_index >= band_energies_.size())
        return 0.0;

    return band_energies_[band_index];
}

double SpectrumAnalyzer::CalculateTotalEnergy() const {
    double sum = 0.0;
    for (double energy : band_energies_)
        sum += energy;

    return sum;
}

void SpectrumAnalyzer::Reset() {
    std::fill(band_energies_.begin(), band_energies_.end(), 0.0);
}

void SpectrumAnalyzer::ToggleActive(bool active) {
    is_active_ = active;
}

size_t SpectrumAnalyzer::GetBandsCount() const {
    return bands_count_;
}

double SpectrumAnalyzer::GetPeakDecayRate() const {
    return peak_decay_rate_;
}

bool SpectrumAnalyzer::IsActive() const {
    return is_active_;
}

const std::vector<double>& SpectrumAnalyzer::GetBandEnergies() const {
    return band_energies_;
}