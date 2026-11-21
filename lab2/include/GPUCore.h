/**
 * @file GPUCore.h
 * @brief Declaration of the GPUCore class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef GPUCORE_H
#define GPUCORE_H

#include <iostream>

/**
 * @brief Class modeling an individual physical graphics processing core die.
 */
class GPUCore {
public:
    /**
     * @brief Constructs a GPU core with specified identity and clock speed.
     * @param core_id Core identifier number.
     * @param clock_mhz Operating clock frequency in MHz.
     */
    explicit GPUCore(int core_id = 0, int clock_mhz = 2200);

    /**
     * @brief Compares two GPU cores for equality.
     * @param other Core to compare with.
     * @return true if ID and clock frequency match.
     */
    bool operator==(const GPUCore& other) const;

    /**
     * @brief Inequality operator.
     * @param other Core to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const GPUCore& other) const;

    /**
     * @brief Stream output operator for formatting core state.
     * @param os Output stream.
     * @param core Core instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const GPUCore& core);

    /**
     * @brief Renders 3D frames, increasing workload and heat generation.
     * @param frame_count Number of visual frames rendered.
     */
    void RenderFrames(int frame_count);

    /**
     * @brief Lowers core temperature via fan or cooling system.
     * @param delta_celsius Temperature drop in Celsius.
     */
    void CoolDown(double delta_celsius);

    /**
     * @brief Adjusts core clock frequency, verifying thermal safety.
     * @param new_clock New target frequency in MHz.
     */
    void SetClockMhz(int new_clock);

    /**
     * @brief Gets core identifier number.
     * @return Core ID.
     */
    int GetCoreId() const;

    /**
     * @brief Gets current operating clock frequency in MHz.
     * @return Clock speed in MHz.
     */
    int GetClockMhz() const;

    /**
     * @brief Gets current temperature in degrees Celsius.
     * @return Temperature.
     */
    double GetTemperatureCelsius() const;

    /**
     * @brief Gets current GPU load percentage.
     * @return Load percentage (0.0 to 100.0).
     */
    double GetLoadPercentage() const;

private:
    int core_id_;
    int clock_mhz_;
    double temperature_celsius_;
    double load_percentage_;
};

#endif