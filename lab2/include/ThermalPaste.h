/**
 * @file ThermalPaste.h
 * @brief Declaration of the ThermalPaste class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef THERMALPASTE_H
#define THERMALPASTE_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling Thermal Interface Material (TIM / thermal paste) between CPU/GPU and heat sink.
 */
class ThermalPaste {
public:
    /**
     * @brief Constructs thermal interface with specified physical properties.
     * @param brand_name Product commercial name.
     * @param thermal_conductivity Thermal conductivity rating in W/(m*K).
     * @param viscosity Viscosity rating in Poise.
     * @param thickness_mm Applied bond-line thickness in millimeters.
     */
    explicit ThermalPaste(const std::string& brand_name = "Arctic MX-6", double thermal_conductivity = 8.5, double viscosity = 45000, double thickness_mm = 0.05);

    /**
     * @brief Compares two thermal paste applications for equality.
     * @param other Thermal paste instance to compare.
     * @return true if brand, conductivity, and thickness match.
     */
    bool operator==(const ThermalPaste& other) const;

    /**
     * @brief Checks inequality.
     * @param other Thermal paste instance to compare.
     * @return true if properties differ.
     */
    bool operator!=(const ThermalPaste& other) const;

    /**
     * @brief Stream output operator for formatting thermal paste status.
     * @param os Output stream.
     * @param paste Thermal paste instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ThermalPaste& paste);

    /**
     * @brief Calculates thermal junction resistance across specified contact surface.
     * @param surface_area_cm2 Contact area in square centimeters.
     * @return Thermal resistance in (K*cm^2)/W.
     */
    double CalculateThermalResistance(double surface_area_cm2) const;

    /**
     * @brief Simulates physical thermal aging and solvent drying over time.
     * @param years Operating elapsed duration in years.
     */
    void DegradeOverTime(double years);

    /**
     * @brief Replaces existing degraded compound with fresh thermal interface.
     * @param new_conductivity New material conductivity in W/(m*K).
     * @param new_thickness Freshly applied bond-line thickness in mm.
     */
    void ReplacePaste(double new_conductivity, double new_thickness);

    /**
     * @brief Determines whether thermal compound maintains effective heat transfer margins.
     * @return true if paste is in good condition.
     */
    bool IsEffective() const;

    /**
     * @brief Evaluates heat transfer efficiency score as a normalized factor (0.0 to 1.0).
     * @return Efficiency factor.
     */
    double EvaluateHeatTransferEfficiency() const;

    /**
     * @brief Gets compound brand name.
     * @return Brand name string.
     */
    std::string GetBrandName() const;

    /**
     * @brief Gets thermal conductivity in W/(m*K).
     * @return Conductivity rating.
     */
    double GetThermalConductivity() const;

    /**
     * @brief Gets viscosity in Poise.
     * @return Viscosity rating.
     */
    double GetViscosity() const;

    /**
     * @brief Gets applied layer thickness in millimeters.
     * @return Thickness in mm.
     */
    double GetThicknessMm() const;

    /**
     * @brief Gets elapsed service lifetime in years.
     * @return Service duration in years.
     */
    double GetServiceYears() const;

    /**
     * @brief Checks if thermal compound has dried out.
     * @return true if paste is dry.
     */
    bool IsDry() const;

private:
    std::string brand_name_;
    double thermal_conductivity_;
    double viscosity_;
    double thickness_mm_;
    double service_years_;
    bool is_dry_;
};

#endif