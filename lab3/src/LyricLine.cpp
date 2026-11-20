/**
 * @file LyricLine.cpp
 * @brief Implementation of LyricLine methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "LyricLine.h"
#include <iomanip>
#include <sstream>
#include <cmath>

LyricLine::LyricLine(double timestamp_sec, const std::string& text, bool is_chorus) :
    timestamp_sec_(timestamp_sec >= 0.0 ? timestamp_sec : 0.0), text_(text), is_chorus_(is_chorus) {}

bool LyricLine::operator==(const LyricLine& other) const {
    const double kEpsilon = 1e-4;
    return std::abs(timestamp_sec_ - other.timestamp_sec_) < kEpsilon &&
           text_ == other.text_ &&
           is_chorus_ == other.is_chorus_;
}

bool LyricLine::operator!=(const LyricLine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const LyricLine& line) {
    os << line.FormatTimestampedLine();
    return os;
}

std::string LyricLine::FormatTimestampedLine() const {
    int total_sec = static_cast<int>(timestamp_sec_);
    int minutes = total_sec / 60;
    int seconds = total_sec % 60;
    int hundredths = static_cast<int>((timestamp_sec_ - total_sec) * 100);

    std::ostringstream oss;
    oss << "[" << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds << "."
        << std::setfill('0') << std::setw(2) << hundredths << "] "
        << (is_chorus_ ? "(Chorus) " : "") << text_;
    return oss.str();
}

bool LyricLine::IsActiveAt(double current_time, double display_duration_sec) const {
    if (current_time < timestamp_sec_)
        return false;

    return current_time <= (timestamp_sec_ + display_duration_sec);
}

void LyricLine::SetText(const std::string& text) {
    text_ = text;
}

void LyricLine::AdjustTimestamp(double delta_sec) {
    timestamp_sec_ += delta_sec;
    if (timestamp_sec_ < 0.0)
        timestamp_sec_ = 0.0;
}

double LyricLine::GetTimestampSec() const {
    return timestamp_sec_;
}

const std::string& LyricLine::GetText() const {
    return text_;
}

bool LyricLine::IsChorus() const {
    return is_chorus_;
}