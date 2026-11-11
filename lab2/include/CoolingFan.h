/**
 * @file CoolingFan.h
 * @brief Declaration of the CoolingFan class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef COOLING_FAN_H
#define COOLING_FAN_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a chassis or heatsink cooling fan with PWM speed control.
 */
class CoolingFan {
public:
    /**
     * @brief Constructs a CoolingFan with physical size, speed range and PWM duty cycle.
     * @param fan_name Fan commercial model name.
     * @param diameter_mm Impeller diameter in millimeters (e.g. 120, 140).
     * @param rpm Current rotational speed in revolutions per minute.
     * @param max_rpm Maximum rated rotational speed in RPM.
     * @param pwm_duty_cycle Initial PWM signal duty percentage (0 to 100).
     */
    explicit CoolingFan(const std::string& fan_name = "Noctua NF-A12x25", int diameter_mm = 120, int rpm = 1000, int max_rpm = 2000, int pwm_duty_cycle = 50);

    /**
     * @brief Compares two cooling fans for equality.
     * @param other CoolingFan instance to compare with.
     * @return true if model, dimensions, speed, and PWM duty match.
     */
    bool operator==(const CoolingFan& other) const;

    /**
     * @brief Inequality operator.
     * @param other CoolingFan instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const CoolingFan& other) const;

    /**
     * @brief Stream output operator for formatting cooling fan state.
     * @param os Output stream.
     * @param fan CoolingFan instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const CoolingFan& fan);

    /**
     * @brief Adjusts the PWM control signal duty cycle, updating current RPM proportionally.
     * @param percent Target speed percentage (clamped between 0 and 100).
     */
    void SetPwmDutyCycle(int percent);

    /**
     * @brief Calculates volumetric airflow delivery in cubic feet per minute (CFM).
     * @return Airflow in CFM.
     */
    double CalculateAirflowCfm() const;

    /**
     * @brief Estimates acoustic noise output in decibels (dBA) at current speed.
     * @return Noise level in dBA.
     */
    double CalculateNoiseLevelDba() const;

    /**
     * @brief Gets fan model name string.
     * @return Fan name string reference.
     */
    const std::string& GetFanName() const;

    /**
     * @brief Gets fan diameter in millimeters.
     * @return Diameter in mm.
     */
    int GetDiameterMm() const;

    /**
     * @brief Gets current rotational speed in RPM.
     * @return Current speed in RPM.
     */
    int GetRpm() const;

    /**
     * @brief Gets maximum rated speed in RPM.
     * @return Maximum speed in RPM.
     */
    int GetMaxRpm() const;

    /**
     * @brief Gets current PWM duty cycle percentage.
     * @return PWM duty percentage (0 to 100).
     */
    int GetPwmDutyCycle() const;

private:
    std::string fan_name_;
    int diameter_mm_;
    int rpm_;
    int max_rpm_;
    int pwm_duty_cycle_;
};

#endif