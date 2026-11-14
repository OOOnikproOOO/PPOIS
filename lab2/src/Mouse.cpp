/**
 * @file Mouse.cpp
 * @brief Implementation of Mouse methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Mouse.h"
#include "ComputerException.h"

Mouse::Mouse(int dpi, int cursor_x, int cursor_y, bool left_button_pressed, bool right_button_pressed) :
    dpi_(dpi), cursor_x_(cursor_x), cursor_y_(cursor_y), left_button_pressed_(left_button_pressed), right_button_pressed_(right_button_pressed) {}

bool Mouse::operator==(const Mouse& other) const {
    return dpi_ == other.dpi_ &&
           cursor_x_ == other.cursor_x_ && cursor_y_ == other.cursor_y_ &&
           left_button_pressed_ == other.left_button_pressed_ &&
           right_button_pressed_ == other.right_button_pressed_;
}

bool Mouse::operator!=(const Mouse& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Mouse& mouse) {
    os << "Mouse [DPI: " << mouse.dpi_ << ", Pos: (" << mouse.cursor_x_ << ", " << mouse.cursor_y_ << "), Left: " << (mouse.left_button_pressed_ ? "Pressed" : "Released") << ", Right: " << (mouse.right_button_pressed_ ? "Pressed" : "Released") << "]";
    return os;
}

void Mouse::Move(int delta_x, int delta_y) {
    cursor_x_ += delta_x;
    cursor_y_ += delta_y;
    if (cursor_x_ < 0) 
        cursor_x_ = 0;
    if (cursor_y_ < 0)
        cursor_y_ = 0;
}

void Mouse::ClickLeft() {
    left_button_pressed_ = true;
}

void Mouse::ReleaseLeft() {
    left_button_pressed_ = false;
}

void Mouse::ClickRight() {
    right_button_pressed_ = true;
}

void Mouse::ReleaseRight() {
    right_button_pressed_ = false;
}

void Mouse::SetDpi(int dpi) {
    if (dpi < 100 || dpi > 32000) 
        throw ComputerException("Mouse DPI must be between 100 and 32000.");
    dpi_ = dpi;
}

int Mouse::GetDpi() const {
    return dpi_;
}

int Mouse::GetCursorX() const {
    return cursor_x_;
}

int Mouse::GetCursorY() const {
    return cursor_y_;
}

bool Mouse::IsLeftButtonPressed() const {
    return left_button_pressed_;
}

bool Mouse::IsRightButtonPressed() const {
    return right_button_pressed_;
}