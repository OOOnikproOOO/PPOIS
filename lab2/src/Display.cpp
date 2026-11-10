/**
 * @file Display.cpp
 * @brief Implementation of Display methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Display.h"
#include "Exceptions.h"

Display::Display(const std::string& model, int resolution_width, int resolution_height, int refresh_rate_hz) :
    model_(model), resolution_width_(resolution_width), resolution_height_(resolution_height), refresh_rate_hz_(refresh_rate_hz), is_powered_on_(true) {}

bool Display::operator==(const Display& other) const {
    return (model_ == other.model_ &&
            resolution_width_ == other.resolution_width_ &&
            resolution_height_ == other.resolution_height_ &&
            refresh_rate_hz_ == other.refresh_rate_hz_ &&
            is_powered_on_ == other.is_powered_on_);
}

bool Display::operator!=(const Display& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Display& display) {
    os << "Display: " << display.model_ << " [" << display.resolution_width_ << "x" << display.resolution_height_ << "@" << display.refresh_rate_hz_ << "Hz, " << (display.is_powered_on_ ? "Power ON" : "Standby") << "]";
    return os;
}

void Display::PowerToggle() {
    is_powered_on_ = !is_powered_on_;
}

void Display::SetResolution(int width, int height) {
    if (width < 640 || width > 7680 || height < 480 || height > 4320)
        throw ComputerException("Invalid display resolution specified: " + std::to_string(width) + "x" + std::to_string(height));
    
    resolution_width_ = width;
    resolution_height_ = height;
}

void Display::SetRefreshRate(int hz) {
    if (hz < 30 || hz > 540)
        throw ComputerException("Invalid refresh rate specified: " + std::to_string(hz) + " Hz.");
    
    refresh_rate_hz_ = hz;
}

long long Display::CalculateTotalPixels() const {
    return resolution_width_ * resolution_height_;
}

std::string Display::GetModel() const {
    return model_;
}

int Display::GetResolutionWidth() const {
    return resolution_width_;
}

int Display::GetResolutionHeight() const {
    return resolution_height_;
}

int Display::GetRefreshRateHz() const {
    return refresh_rate_hz_;
}

bool Display::IsPoweredOn() const {
    return is_powered_on_;
}