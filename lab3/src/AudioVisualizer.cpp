/**
 * @file AudioVisualizer.cpp
 * @brief Implementation of AudioVisualizer methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioVisualizer.h"
#include <cmath>
#include <sstream>

AudioVisualizer::AudioVisualizer(const std::string& mode, int refresh_rate_hz) :
    visualization_mode_(mode), left_peak_(0.0), right_peak_(0.0), refresh_rate_hz_(refresh_rate_hz < 10 ? 10 : (refresh_rate_hz > 120 ? 120 : refresh_rate_hz)) {}

bool AudioVisualizer::operator==(const AudioVisualizer& other) const {
    const double kEpsilon = 1e-4;
    return visualization_mode_ == other.visualization_mode_ &&
           std::abs(left_peak_ - other.left_peak_) < kEpsilon &&
           std::abs(right_peak_ - other.right_peak_) < kEpsilon &&
           refresh_rate_hz_ == other.refresh_rate_hz_;
}

bool AudioVisualizer::operator!=(const AudioVisualizer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioVisualizer& viz) {
    os << "Visualizer[Mode: " << viz.visualization_mode_ << ", Left: " << viz.left_peak_ << ", Right: " << viz.right_peak_ << "]";
    return os;
}

void AudioVisualizer::UpdateLevels(const AudioSample& sample) {
    double l = std::abs(sample.GetLeftChannel());
    double r = std::abs(sample.GetRightChannel());

    if (l > 1.0)
        l = 1.0;

    if (r > 1.0)
        r = 1.0;

    if (l > left_peak_)
        left_peak_ = l;

    if (r > right_peak_)
        right_peak_ = r;
}

std::string AudioVisualizer::RenderAsciiBar(double level, int bar_width) const {
    if (level < 0.0)
        level = 0.0;

    if (level > 1.0)
        level = 1.0;

    if (bar_width < 5)
        bar_width = 5;

    int filled = static_cast<int>(level * bar_width);
    std::string bar = "[";
    for (int i = 0; i < filled; i++)
        bar += "=";

    for (int i = filled; i < bar_width; i++)
        bar += " ";

    bar += "]";
    return bar;
}

std::string AudioVisualizer::RenderStereoVuMeter() const {
    std::ostringstream oss;
    oss << "L: " << RenderAsciiBar(left_peak_, 12) << " | R: " << RenderAsciiBar(right_peak_, 12);
    return oss.str();
}

void AudioVisualizer::ResetPeaks() {
    left_peak_ = 0.0;
    right_peak_ = 0.0;
}

void AudioVisualizer::SetMode(const std::string& mode) {
    visualization_mode_ = mode;
}

const std::string& AudioVisualizer::GetMode() const {
    return visualization_mode_;
}

double AudioVisualizer::GetLeftPeak() const {
    return left_peak_;
}

double AudioVisualizer::GetRightPeak() const {
    return right_peak_;
}

int AudioVisualizer::GetRefreshRateHz() const {
    return refresh_rate_hz_;
}