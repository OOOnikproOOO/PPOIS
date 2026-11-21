/**
 * @file PowerSupply.h
 * @brief Declaration of the PowerSupply class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef POWER_SUPPLY_H
#define POWER_SUPPLY_H

#include <iostream>
#include <string>
#include <vector>
#include "PowerRail.h"

/**
 * @brief Class modeling the main Power Supply Unit (PSU) converting AC mains to DC rails.
 */
class PowerSupply {
public:
    /**
     * @brief Constructs a PowerSupply unit with wattage capacity and efficiency certification.
     * @param model_name Commercial PSU model name.
     * @param rated_wattage Maximum continuous power capacity in Watts.
     * @param efficiency_rating 80 PLUS efficiency certification label.
     * @param is_powered_on Initial PSU power state.
     */
    explicit PowerSupply(const std::string& model_name = "Corsair RM850x", int rated_wattage = 850, const std::string& efficiency_rating = "80 PLUS Gold", bool is_powered_on = false);

    /**
     * @brief Compares two power supply units for equality.
     * @param other PowerSupply instance to compare with.
     * @return true if model, capacity, rating, and state match.
     */
    bool operator==(const PowerSupply& other) const;

    /**
     * @brief Inequality operator.
     * @param other PowerSupply instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PowerSupply& other) const;

    /**
     * @brief Stream output operator for formatting PSU status.
     * @param os Output stream.
     * @param psu PowerSupply instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PowerSupply& psu);

    /**
     * @brief Registers a DC output power rail to the power supply.
     * @param rail PowerRail instance to add.
     */
    void AddRail(const PowerRail& rail);

    /**
     * @brief Powers on the PSU and activates DC output rails.
     */
    void PowerOn();

    /**
     * @brief Switches the PSU off into standby mode.
     */
    void PowerOff();

    /**
     * @brief Calculates total combined power draw in Watts across all DC rails.
     * @return Total power draw in Watts.
     */
    int CalculateTotalPowerDrawWatts() const;

    /**
     * @brief Calculates PSU electrical efficiency factor at a specified wattage load.
     * @param load_watts Current system power demand in Watts.
     * @return Efficiency ratio (e.g. 0.90 for 90%).
     */
    double CalculateEfficiencyAtLoad(int load_watts) const;

    /**
     * @brief Gets commercial PSU model name.
     * @return Model name string reference.
     */
    const std::string& GetModelName() const;

    /**
     * @brief Gets continuous rated wattage capacity.
     * @return Rated power in Watts.
     */
    int GetRatedWattage() const;

    /**
     * @brief Gets 80 PLUS certification string.
     * @return Efficiency rating label reference.
     */
    const std::string& GetEfficiencyRating() const;

    /**
     * @brief Checks whether the PSU is currently powered on.
     * @return true if active.
     */
    bool IsPoweredOn() const;

    /**
     * @brief Gets total count of registered DC rails.
     * @return Rail count.
     */
    int GetRailCount() const;

    /**
     * @brief Gets reference to a DC power rail at the specified index.
     * @param index Rail index.
     * @return Reference to PowerRail.
     */
    PowerRail& GetRail(int index);
    const PowerRail& GetRail(int index) const;

private:
    std::string model_name_;
    int rated_wattage_;
    std::string efficiency_rating_;
    bool is_powered_on_;
    std::vector<PowerRail> rails_;
};

#endif