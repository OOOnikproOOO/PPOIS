/**
 * @file Keyboard.cpp
 * @brief Implementation of Keyboard methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Keyboard.h"
#include "ComputerException.h"

Keyboard::Keyboard(const std::string& layout, const std::string& switch_type, bool rgb_backlight) :
    layout_(layout), switch_type_(switch_type), rgb_backlight_(rgb_backlight), input_buffer_("") {}

bool Keyboard::operator==(const Keyboard& other) const {
    return layout_ == other.layout_ && switch_type_ == other.switch_type_ &&
           rgb_backlight_ == other.rgb_backlight_ && input_buffer_ == other.input_buffer_;
}

bool Keyboard::operator!=(const Keyboard& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Keyboard& kbd) {
    os << "Keyboard [" << kbd.layout_ << ", " << kbd.switch_type_ << ", RGB: " << (kbd.rgb_backlight_ ? "ON" : "OFF") << ", Buffer: '" << kbd.input_buffer_ << "']";
    return os;
}

void Keyboard::TypeText(const std::string& text) {
    input_buffer_ += text;
}

void Keyboard::ClearBuffer() {
    input_buffer_.clear();
}

void Keyboard::ToggleBacklight(bool enabled) {
    rgb_backlight_ = enabled;
}

void Keyboard::SetLayout(const std::string& layout) {
    if (layout.empty()) 
        throw ComputerException("Keyboard layout name cannot be empty.");
    layout_ = layout;
}

const std::string& Keyboard::GetLayout() const {
    return layout_;
}

const std::string& Keyboard::GetSwitchType() const {
    return switch_type_;
}

const std::string& Keyboard::GetInputBuffer() const {
    return input_buffer_;
}

bool Keyboard::IsBacklightOn() const {
    return rgb_backlight_;
}