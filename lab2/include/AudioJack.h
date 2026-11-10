/**
 * @file AudioJack.h
 * @brief Declaration of the AudioJack class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef AUDIOJACK_H
#define AUDIOJACK_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling an individual analog audio jack.
 */
class AudioJack {
public:
    /**
     * @brief Constructs an audio jack with specified function and impedance rating.
     * @param port_type Functional role ("Line Out 3.5mm", "Mic In 3.5mm", "Headphone Out").
     * @param color_code PC99 standard color identifier ("Green", "Pink", "Blue", "Black").
     * @param impedance_ohms Internal impedance specification in Ohms.
     */
    explicit AudioJack(const std::string& port_type = "Line Out 3.5mm", const std::string& color_code = "Green", double impedance_ohms = 32.0);

    /**
     * @brief Compares two audio jacks for equality.
     * @param other AudioJack to compare with.
     * @return true if properties match.
     */
    bool operator==(const AudioJack& other) const;

    /**
     * @brief Inequality operator.
     * @param other AudioJack to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const AudioJack& other) const;

    /**
     * @brief Stream output operator for formatting audio jack status.
     * @param os Output stream.
     * @param jack AudioJack instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AudioJack& jack);

    /**
     * @brief Simulates inserting an analog audio cable jack plug.
     */
    void PlugIn();

    /**
     * @brief Simulates unplugging the audio cable from the socket.
     */
    void Unplug();

    /**
     * @brief Verifies whether external headphone impedance safely matches internal circuit ratings.
     * @param load_ohms External device impedance in Ohms.
     * @return true if impedance is within safe driving range.
     */
    bool VerifyImpedanceMatch(double load_ohms) const;

    /**
     * @brief Gets port functional purpose string.
     * @return Port type name.
     */
    std::string GetPortType() const;

    /**
     * @brief Gets socket PC99 color code.
     * @return Color name string.
     */
    std::string GetColorCode() const;

    /**
     * @brief Checks if a cable is currently plugged into this jack.
     * @return true if plugged.
     */
    bool IsPlugged() const;

    /**
     * @brief Gets internal circuit impedance in Ohms.
     * @return Impedance in Ohms.
     */
    double GetImpedanceOhms() const;

private:
    std::string port_type_;
    std::string color_code_;
    bool is_plugged_;
    double impedance_ohms_;
};

#endif