/**
 * @file CPUCore.h
 * @brief Declaration of the CPUCore class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef CPUCORE_H
#define CPUCORE_H

#include <iostream>

/**
 * @brief Class modeling an individual CPU physical processing core.
 */
class CPUCore {
public:
    /**
     * @brief Constructs an execution core with specified parameters.
     * @param core_id Core index identifier.
     * @param base_clock_mhz Base frequency in MHz.
     * @param enable_hyperthreading Hyper-threading flag.
     */
    explicit CPUCore(int core_id = 0, int base_clock_mhz = 3200, bool enable_hyperthreading = true);

    /**
     * @brief Compares two cores for equality based on ID and clock properties.
     * @param other Core to compare with.
     * @return true if properties match.
     */
    bool operator==(const CPUCore& other) const;

    /**
     * @brief Checks inequality.
     * @param other Core to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const CPUCore& other) const;

    /**
     * @brief Stream output operator for formatting core status.
     * @param os Output stream.
     * @param core Core instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const CPUCore& core);

    /**
     * @brief Executes instructions, simulating processor workload.
     * @param instruction_count Number of machine instructions to process.
     */
    void ExecuteInstructions(long long instruction_count);

    /**
     * @brief Sets current computational load percentage.
     * @param load Load value from 0.0 to 100.0.
     */
    void UpdateLoad(double load);

    /**
     * @brief Lowers core temperature via cooling.
     * @param delta_celsius Temperature drop in degrees Celsius.
     */
    void CoolDown(double delta_celsius);

    /**
     * @brief Attempts to boost core frequency if thermal margins allow.
     * @param target_mhz Desired boosted clock frequency.
     * @return true if boost succeeded.
     */
    bool BoostClock(int target_mhz);

    /**
     * @brief Reduces core clock speed to protect against thermal damage.
     * @param factor Throttling multiplier (e.g. 0.7 for 30% reduction).
     */
    void Throttle(double factor);

    /**
     * @brief Gets core identifier.
     * @return Core index.
     */
    int GetCoreId() const;

    /**
     * @brief Gets base clock frequency in MHz.
     * @return Base frequency.
     */
    int GetBaseClockMhz() const;

    /**
     * @brief Gets current operating clock frequency in MHz.
     * @return Operating frequency.
     */
    int GetCurrentClockMhz() const;

    /**
     * @brief Gets current workload percentage.
     * @return Workload from 0.0 to 100.0.
     */
    double GetLoadPercentage() const;

    /**
     * @brief Gets current core temperature in Celsius.
     * @return Temperature in Celsius.
     */
    double GetTemperatureCelsius() const;

    /**
     * @brief Checks if hyper-threading is enabled on this core.
     * @return true if hyper-threading is active.
     */
    bool IsHyperthreadingActive() const;

private:
    int core_id_;
    int base_clock_mhz_;
    int current_clock_mhz_;
    double load_percentage_;
    double temperature_celsius_;
    bool is_hyperthreading_active_;
};

#endif