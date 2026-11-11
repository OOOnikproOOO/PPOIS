/**
 * @file CoolingSystem.h
 * @brief Declaration of the CoolingSystem class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef COOLING_SYSTEM_H
#define COOLING_SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include "CoolingFan.h"
#include "LiquidCooler.h"

/**
 * @brief Class modeling a unified thermal management subsystem uniting chassis fans and an AIO liquid cooler.
 */
class CoolingSystem {
public:
    /**
     * @brief Constructs a CoolingSystem with an operating fan curve profile and liquid cooling loop.
     * @param fan_profile Cooling profile preset name ("Silent", "Standard", "Performance", "Full Speed").
     * @param target_temperature_celsius Target thermal equilibrium temperature in Celsius.
     * @param liquid_cooler Integrated AIO liquid cooling unit.
     */
    explicit CoolingSystem(const std::string& fan_profile = "Standard", double target_temperature_celsius = 65.0, const LiquidCooler& liquid_cooler = LiquidCooler());

    /**
     * @brief Compares two cooling systems for equality.
     * @param other CoolingSystem instance to compare with.
     * @return true if profile, target temp, and liquid cooler match.
     */
    bool operator==(const CoolingSystem& other) const;

    /**
     * @brief Inequality operator.
     * @param other CoolingSystem instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const CoolingSystem& other) const;

    /**
     * @brief Stream output operator for formatting cooling subsystem status.
     * @param os Output stream.
     * @param cooling CoolingSystem instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const CoolingSystem& cooling);

    /**
     * @brief Installs an additional chassis cooling fan into the system hub.
     * @param fan CoolingFan instance to add.
     */
    void AddFan(const CoolingFan& fan);

    /**
     * @brief Applies a cooling curve preset, synchronizing PWM fan speeds and pump RPM.
     * @param profile Preset name ("Silent", "Standard", "Performance", "Full Speed").
     */
    void ApplyProfile(const std::string& profile);

    /**
     * @brief Calculates total combined volumetric airflow across all active case fans.
     * @return Total airflow in CFM.
     */
    double CalculateTotalAirflowCfm() const;

    /**
     * @brief Gets active fan speed profile name.
     * @return Profile string reference.
     */
    const std::string& GetFanProfile() const;

    /**
     * @brief Gets target thermal equilibrium temperature in Celsius.
     * @return Target temperature.
     */
    double GetTargetTemperatureCelsius() const;

    /**
     * @brief Gets total count of registered chassis cooling fans.
     * @return Fan count.
     */
    int GetFanCount() const;

    /**
     * @brief Gets reference to the integrated AIO liquid cooler.
     * @return Reference to LiquidCooler.
     */
    LiquidCooler& GetLiquidCooler();
    const LiquidCooler& GetLiquidCooler() const;

    /**
     * @brief Gets reference to a chassis fan at the specified index.
     * @param index Fan slot index.
     * @return Reference to CoolingFan.
     */
    CoolingFan& GetFan(int index);
    const CoolingFan& GetFan(int index) const;

private:
    std::string fan_profile_;
    double target_temperature_celsius_;
    LiquidCooler liquid_cooler_;
    std::vector<CoolingFan> fans_;
};

#endif