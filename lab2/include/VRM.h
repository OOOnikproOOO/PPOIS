/**
 * @file VRM.h
 * @brief Declaration of the VRM class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef VRM_H
#define VRM_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a Voltage Regulator Module converting 12V DC to CPU VCore.
 */
class VRM {
public:
    /**
     * @brief Constructs a VRM subsystem with specified phase count, voltage, temperature and efficiency.
     * @param phase_count Number of power delivery phases.
     * @param vcore_voltage Target CPU core voltage in Volts.
     * @param temperature_celsius Initial VRM heatsink temperature in Celsius.
     * @param efficiency_percentage Power conversion efficiency percentage.
     */
    explicit VRM(int phase_count = 16, double vcore_voltage = 1.25, double temperature_celsius = 42.0, double efficiency_percentage = 92.0);

    /**
     * @brief Compares two VRM modules for equality.
     * @param other VRM instance to compare with.
     * @return true if all electrical and thermal attributes match.
     */
    bool operator==(const VRM& other) const;

    /**
     * @brief Inequality operator.
     * @param other VRM instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const VRM& other) const;

    /**
     * @brief Stream output operator for formatting VRM status.
     * @param os Output stream.
     * @param vrm VRM instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const VRM& vrm);

    /**
     * @brief Sets target VCore output voltage within safe processor bounds.
     * @param volts Desired VCore voltage in Volts (0.5V to 1.85V).
     */
    void SetVCoreVoltage(double volts);

    /**
     * @brief Supplies electrical current load to the CPU, generating conversion heat.
     * @param current_amperes Electric current drawn in Amperes.
     */
    void SupplyCurrent(double current_amperes);

    /**
     * @brief Lowers VRM heatsink temperature via system airflow.
     * @param delta_celsius Temperature decrease in Celsius.
     */
    void CoolDown(double delta_celsius);

    /**
     * @brief Calculates electrical power dissipated as heat during conversion.
     * @param current_amperes Electric current load in Amperes.
     * @return Power loss in Watts.
     */
    double CalculatePowerLossWatts(double current_amperes) const;

    /**
     * @brief Gets total number of power regulator phases.
     * @return Phase count.
     */
    int GetPhaseCount() const;

    /**
     * @brief Gets current VCore output voltage in Volts.
     * @return Voltage in Volts.
     */
    double GetVCoreVoltage() const;

    /**
     * @brief Gets current VRM temperature in degrees Celsius.
     * @return Temperature.
     */
    double GetTemperatureCelsius() const;

    /**
     * @brief Gets power conversion efficiency percentage.
     * @return Efficiency percentage.
     */
    double GetEfficiencyPercentage() const;

private:
    int phase_count_;
    double vcore_voltage_;
    double temperature_celsius_;
    double efficiency_percentage_;
};

#endif