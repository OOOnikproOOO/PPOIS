/**
 * @file AudioSample.cpp
 * @brief Implementation of AudioSample methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioSample.h"
#include <cmath>

AudioSample::AudioSample(double left, double right, int bit_depth) : left_channel_(left), right_channel_(right), bit_depth_(bit_depth), is_clipped_(false) {
    Normalize(1.0);
}

bool AudioSample::operator==(const AudioSample& other) const {
    const double kEpsilon = 1e-5;
    return std::abs(left_channel_ - other.left_channel_) < kEpsilon &&
           std::abs(right_channel_ - other.right_channel_) < kEpsilon &&
           bit_depth_ == other.bit_depth_ &&
           is_clipped_ == other.is_clipped_;
}

bool AudioSample::operator!=(const AudioSample& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioSample& sample) {
    os << "Sample[L:" << sample.left_channel_ << ", R:" << sample.right_channel_ << ", " << sample.bit_depth_ << "-bit]";
    return os;
}

void AudioSample::Amplify(double factor) {
    left_channel_ *= factor;
    right_channel_ *= factor;
    Normalize(1.0);
}

void AudioSample::Normalize(double peak_limit) {
    if (std::abs(left_channel_) > peak_limit) {
        left_channel_ = (left_channel_ > 0) ? peak_limit : -peak_limit;
        is_clipped_ = true;
    }
    if (std::abs(right_channel_) > peak_limit) {
        right_channel_ = (right_channel_ > 0) ? peak_limit : -peak_limit;
        is_clipped_ = true;
    }
}

void AudioSample::ConvertToMono() {
    double mono = (left_channel_ + right_channel_) * 0.5;
    left_channel_ = mono;
    right_channel_ = mono;
}

double AudioSample::CalculatePowerRms() const {
    return std::sqrt(0.5 * (left_channel_ * left_channel_ + right_channel_ * right_channel_));
}

double AudioSample::GetLeftChannel() const {
    return left_channel_;
}

double AudioSample::GetRightChannel() const {
    return right_channel_;
}

int AudioSample::GetBitDepth() const {
    return bit_depth_;
}

bool AudioSample::IsClipped() const {
    return is_clipped_;
}