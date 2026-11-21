/**
 * @file LiquidCooler.h
 * @brief Declaration of the LiquidCooler class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef LIQUID_COOLER_H
#define LIQUID_COOLER_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling an All-In-One (AIO) liquid cooling loop with pump, radiator and coolant.
 */
class LiquidCooler {
public:
    /**
     * @brief Constructs a LiquidCooler loop with radiator size, pump speed and coolant state.
     * @param model_name Commercial AIO cooler model name.
     * @param radiator_size_mm Radiator physical size in millimeters (e.g. 240, 280, 360).
     * @param pump_rpm Initial pump speed in revolutions per minute.
     * @param coolant_temperature_celsius Initial liquid coolant temperature in Celsius.
     * @param flow_rate_lph Coolant circulation flow rate in liters per hour.
     */
    explicit LiquidCooler(const std::string& model_name = "Arctic Liquid Freezer II 360", int radiator_size_mm = 360, int pump_rpm = 2800, double coolant_temperature_celsius = 30.0, double flow_rate_lph = 150.0);

    /**
     * @brief Compares two liquid coolers for equality.
     * @param other LiquidCooler instance to compare with.
     * @return true if model, radiator size, pump speed, and coolant state match.
     */
    bool operator==(const LiquidCooler& other) const;

    /**
     * @brief Inequality operator.
     * @param other LiquidCooler instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const LiquidCooler& other) const;

    /**
     * @brief Stream output operator for formatting liquid cooler telemetry.
     * @param os Output stream.
     * @param cooler LiquidCooler instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const LiquidCooler& cooler);

    /**
     * @brief Sets the circulation water pump rotational speed and recalculates flow rate.
     * @param target_rpm Target pump speed in RPM (minimum 800 RPM).
     */
    void SetPumpSpeed(int target_rpm);

    /**
     * @brief Simulates thermal energy transfer from the CPU die into the coolant loop.
     * @param heat_watts Thermal heat load in Watts.
     */
    void AbsorbHeat(double heat_watts);

    /**
     * @brief Lowers coolant temperature as radiator fins dissipate heat to ambient air.
     * @param delta_celsius Coolant temperature decrease in Celsius.
     */
    void DissipateHeat(double delta_celsius);

    /**
     * @brief Gets AIO cooler commercial model name.
     * @return Model name string reference.
     */
    const std::string& GetModelName() const;

    /**
     * @brief Gets radiator size in millimeters.
     * @return Radiator length in mm.
     */
    int GetRadiatorSizeMm() const;

    /**
     * @brief Gets current water pump speed in RPM.
     * @return Pump speed in RPM.
     */
    int GetPumpRpm() const;

    /**
     * @brief Gets current coolant temperature in degrees Celsius.
     * @return Coolant temperature.
     */
    double GetCoolantTemperatureCelsius() const;

    /**
     * @brief Gets current coolant circulation rate in liters per hour.
     * @return Flow rate in L/h.
     */
    double GetFlowRateLph() const;

private:
    std::string model_name_;
    int radiator_size_mm_;
    int pump_rpm_;
    double coolant_temperature_celsius_;
    double flow_rate_lph_;
};

#endif