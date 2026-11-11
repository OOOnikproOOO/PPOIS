/**
 * @file PowerRail.h
 * @brief Declaration of the PowerRail class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef POWER_RAIL_H
#define POWER_RAIL_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling an individual DC power delivery rail (+12V, +5V, +3.3V) of a power supply.
 */
class PowerRail {
public:
    /**
     * @brief Constructs a PowerRail with nominal voltage, initial load and current limit.
     * @param rail_name Rail label identifier ("+12V", "+5V", "+3.3V").
     * @param nominal_voltage Standard DC output voltage in Volts.
     * @param current_amperes Initial electrical current load in Amperes.
     * @param max_amperes Maximum rated current capacity in Amperes.
     */
    explicit PowerRail(const std::string& rail_name = "+12V", double nominal_voltage = 12.0, double current_amperes = 0.0, double max_amperes = 70.0);

    /**
     * @brief Compares two power rails for equality.
     * @param other PowerRail instance to compare with.
     * @return true if voltage, load, and current limits match.
     */
    bool operator==(const PowerRail& other) const;

    /**
     * @brief Inequality operator.
     * @param other PowerRail instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PowerRail& other) const;

    /**
     * @brief Stream output operator for formatting power rail electrical telemetry.
     * @param os Output stream.
     * @param rail PowerRail instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PowerRail& rail);

    /**
     * @brief Draws additional electrical current from the rail.
     * @param amperes Additional current in Amperes.
     */
    void DrawCurrent(double amperes);

    /**
     * @brief Releases electrical current load when components become idle.
     * @param amperes Current reduction in Amperes.
     */
    void ReleaseCurrent(double amperes);

    /**
     * @brief Calculates active power output delivered by this rail in Watts.
     * @return Power output in Watts.
     */
    double CalculateCurrentPowerWatts() const;

    /**
     * @brief Gets rail designation string.
     * @return Rail name string reference.
     */
    const std::string& GetRailName() const;

    /**
     * @brief Gets nominal DC rail voltage in Volts.
     * @return Nominal voltage.
     */
    double GetNominalVoltage() const;

    /**
     * @brief Gets current electrical load in Amperes.
     * @return Current draw in Amperes.
     */
    double GetCurrentAmperes() const;

    /**
     * @brief Gets maximum rated current limit in Amperes.
     * @return Maximum current in Amperes.
     */
    double GetMaxAmperes() const;

private:
    std::string rail_name_;
    double nominal_voltage_;
    double current_amperes_;
    double max_amperes_;
};

#endif