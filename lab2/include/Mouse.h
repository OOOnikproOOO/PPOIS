/**
 * @file Mouse.h
 * @brief Declaration of the Mouse class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <string>

/**
 * @brief Represents an optical computer mouse peripheral with coordinate tracking and button states.
 */
class Mouse {
public:
    /**
     * @brief Constructs a Mouse instance.
     * @param dpi Optical sensor sensitivity (DPI).
     * @param cursor_x Initial horizontal cursor coordinate.
     * @param cursor_y Initial vertical cursor coordinate.
     * @param left_button_pressed Initial left button state.
     * @param right_button_pressed Initial right button state.
     */
    explicit Mouse(int dpi = 1600, int cursor_x = 960, int cursor_y = 540, bool left_button_pressed = false, bool right_button_pressed = false);

    /**
     * @brief Equality operator comparing mouse telemetry and buttons.
     * @param other Another Mouse instance.
     * @return true if mouse states match.
     */
    bool operator==(const Mouse& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another Mouse instance.
     * @return true if mouse states differ.
     */
    bool operator!=(const Mouse& other) const;

    /**
     * @brief Stream output operator for formatting mouse telemetry.
     * @param os Output stream.
     * @param mouse Mouse instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Mouse& mouse);

    /**
     * @brief Moves cursor by delta offsets.
     * @param delta_x Horizontal pixel shift.
     * @param delta_y Vertical pixel shift.
     */
    void Move(int delta_x, int delta_y);

    /**
     * @brief Presses the primary left mouse button.
     */
    void ClickLeft();

    /**
     * @brief Releases the primary left mouse button.
     */
    void ReleaseLeft();

    /**
     * @brief Presses the secondary right mouse button.
     */
    void ClickRight();

    /**
     * @brief Releases the secondary right mouse button.
     */
    void ReleaseRight();

    /**
     * @brief Calibrates sensor sensitivity DPI.
     * @param dpi Target DPI (100 to 32000).
     */
    void SetDpi(int dpi);

    /**
     * @brief Gets current sensor DPI.
     * @return Sensor DPI.
     */
    int GetDpi() const;

    /**
     * @brief Gets horizontal cursor coordinate X.
     * @return Cursor X.
     */
    int GetCursorX() const;

    /**
     * @brief Gets vertical cursor coordinate Y.
     * @return Cursor Y.
     */
    int GetCursorY() const;

    /**
     * @brief Checks whether left mouse button is currently held down.
     * @return true if pressed.
     */
    bool IsLeftButtonPressed() const;

    /**
     * @brief Checks whether right mouse button is currently held down.
     * @return true if pressed.
     */
    bool IsRightButtonPressed() const;

private:
    int dpi_;
    int cursor_x_;
    int cursor_y_;
    bool left_button_pressed_;
    bool right_button_pressed_;
};

#endif