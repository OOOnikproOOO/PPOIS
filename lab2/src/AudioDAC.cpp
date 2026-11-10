/**
 * @file AudioDAC.cpp
 * @brief Implementation of AudioDAC member methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioDAC.h"
#include "Exceptions.h"

AudioDAC::AudioDAC(int sampling_rate_hz, int bit_depth, double snr_db) :
    sampling_rate_hz_(sampling_rate_hz), bit_depth_(bit_depth), snr_db_(snr_db), is_active_(true) {}

bool AudioDAC::operator==(const AudioDAC& other) const {
    return (sampling_rate_hz_ == other.sampling_rate_hz_ &&
            bit_depth_ == other.bit_depth_ &&
            snr_db_ == other.snr_db_ &&
            is_active_ == other.is_active_);
}

bool AudioDAC::operator!=(const AudioDAC& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioDAC& dac) {
    os << "AudioDAC [" << dac.sampling_rate_hz_ << " Hz, " << dac.bit_depth_ << "-bit, SNR: " << dac.snr_db_ << " dB, " << (dac.is_active_ ? "Active" : "Muted") << "]";
    return os;
}

bool AudioDAC::ConvertDigitalToAnalog(int sample_count) {
    if (!is_active_)
        return false;
    
    if (sample_count <= 0)
        return false;
    
    return true;
}

void AudioDAC::SetFormat(int sampling_rate_hz, int bit_depth) {
    if (sampling_rate_hz < 8000 || sampling_rate_hz > 384000)
        throw ComputerException("Unsupported audio DAC sample rate requested: " + std::to_string(sampling_rate_hz) + " Hz");
    
    if (bit_depth != 16 && bit_depth != 24 && bit_depth != 32)
        throw ComputerException("Unsupported audio DAC bit depth requested: " + std::to_string(bit_depth) + "-bit");
    
    sampling_rate_hz_ = sampling_rate_hz;
    bit_depth_ = bit_depth;
}

double AudioDAC::CalculateDynamicRangeDb() const {
    return bit_depth_ * 6.02;
}

int AudioDAC::GetSamplingRateHz() const {
    return sampling_rate_hz_;
}

int AudioDAC::GetBitDepth() const {
    return bit_depth_;
}

double AudioDAC::GetSnrDb() const {
    return snr_db_;
}

bool AudioDAC::IsActive() const {
    return is_active_;
}