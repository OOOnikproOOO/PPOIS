/**
 * @file Keyboard.h
 * @brief Declaration of the Keyboard class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include <string>

/**
 * @brief Represents an input keyboard peripheral device with key buffering and RGB lighting.
 */
class Keyboard {
public:
    /**
     * @brief Constructs a Keyboard instance.
     * @param layout Keyboard language layout (e.g. "ENG" or "RUS").
     * @param switch_type Mechanical or membrane switch mechanism.
     * @param rgb_backlight Whether RGB lighting is active.
     */
    explicit Keyboard(const std::string& layout = "ENG", const std::string& switch_type = "Mechanical Red", bool rgb_backlight = true);

    /**
     * @brief Equality operator comparing keyboard configurations and buffers.
     * @param other Another Keyboard instance.
     * @return true if keyboards match.
     */
    bool operator==(const Keyboard& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another Keyboard instance.
     * @return true if keyboards differ.
     */
    bool operator!=(const Keyboard& other) const;

    /**
     * @brief Stream output operator for formatting keyboard status.
     * @param os Output stream.
     * @param kbd Keyboard instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Keyboard& kbd);

    /**
     * @brief Types text into the input buffer.
     * @param text String payload to append to the buffer.
     */
    void TypeText(const std::string& text);

    /**
     * @brief Clears the current keystroke input buffer.
     */
    void ClearBuffer();

    /**
     * @brief Toggles keyboard RGB backlighting.
     * @param enabled Target backlight state.
     */
    void ToggleBacklight(bool enabled);

    /**
     * @brief Sets keyboard keycap language layout.
     * @param layout New layout string.
     */
    void SetLayout(const std::string& layout);

    /**
     * @brief Gets active layout string.
     * @return Layout name.
     */
    const std::string& GetLayout() const;

    /**
     * @brief Gets switch mechanism type.
     * @return Switch type string.
     */
    const std::string& GetSwitchType() const;

    /**
     * @brief Gets accumulated keystroke input buffer.
     * @return Input buffer string.
     */
    const std::string& GetInputBuffer() const;

    /**
     * @brief Checks whether RGB backlighting is currently enabled.
     * @return true if backlight is on.
     */
    bool IsBacklightOn() const;

private:
    std::string layout_;
    std::string switch_type_;
    bool rgb_backlight_;
    std::string input_buffer_;
};

#endif