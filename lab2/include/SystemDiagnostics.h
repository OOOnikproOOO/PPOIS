/**
 * @file SystemDiagnostics.h
 * @brief Declaration of the SystemDiagnostics class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SYSTEMDIAGNOSTICS_H
#define SYSTEMDIAGNOSTICS_H

#include <iostream>

/**
 * @brief Represents a system hardware diagnostics monitor checking thermal, electrical and operational health.
 */
class SystemDiagnostics {
public:
    /**
     * @brief Constructs a SystemDiagnostics monitor.
     * @param all_systems_nominal Initial nominal status flag.
     * @param warnings_count Active warning incidents counter.
     * @param max_recorded_temp Peak recorded hardware temperature.
     * @param total_power_draw Active power consumption in Watts.
     */
    explicit SystemDiagnostics(bool all_systems_nominal = true, int warnings_count = 0, double max_recorded_temp = 35.0, double total_power_draw = 0.0);

    /**
     * @brief Equality operator comparing diagnostic telemetry.
     * @param other Another SystemDiagnostics instance.
     * @return true if diagnostics match.
     */
    bool operator==(const SystemDiagnostics& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another SystemDiagnostics instance.
     * @return true if diagnostics differ.
     */
    bool operator!=(const SystemDiagnostics& other) const;

    /**
     * @brief Stream output operator for formatting diagnostics telemetry.
     * @param os Output stream.
     * @param diag SystemDiagnostics instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SystemDiagnostics& diag);

    /**
     * @brief Evaluates hardware component temperatures against thermal limits.
     * @param cpu_temp Processor temperature in Celsius.
     * @param gpu_temp Graphics processor temperature in Celsius.
     * @param vrm_temp Motherboard VRM temperature in Celsius.
     * @return true if all temperatures stay below threshold.
     */
    bool DiagnoseTemperatures(double cpu_temp, double gpu_temp, double vrm_temp);

    /**
     * @brief Evaluates electrical load against power supply rated wattage.
     * @param power_draw_w Current electrical draw in Watts.
     * @param rated_w Power supply capacity in Watts.
     * @return true if power draw is within capacity.
     */
    bool DiagnosePower(int power_draw_w, int rated_w);

    /**
     * @brief Clears diagnostic warning counters and resets nominal state.
     */
    void ResetDiagnostics();

    /**
     * @brief Records a system operational incident.
     */
    void RecordIncident();

    /**
     * @brief Checks whether all hardware subsystems operate within nominal bounds.
     * @return true if nominal.
     */
    bool IsNominal() const;

    /**
     * @brief Gets active warning incidents count.
     * @return Warning count.
     */
    int GetWarningsCount() const;

    /**
     * @brief Gets highest recorded hardware temperature in Celsius.
     * @return Peak temperature.
     */
    double GetMaxRecordedTemp() const;

    /**
     * @brief Gets recorded total power consumption in Watts.
     * @return Power draw in Watts.
     */
    double GetTotalPowerDraw() const;

private:
    bool all_systems_nominal_;
    int warnings_count_;
    double max_recorded_temp_;
    double total_power_draw_;
};

#endif