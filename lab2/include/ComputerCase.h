/**
 * @file ComputerCase.h
 * @brief Declaration of the ComputerCase class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef COMPUTER_CASE_H
#define COMPUTER_CASE_H

#include <iostream>
#include <string>

/**
 * @brief Class modeling a PC chassis with form-factor compatibility, clearance limits and air filtration.
 */
class ComputerCase {
public:
    /**
     * @brief Constructs a ComputerCase chassis with physical clearances and filter dust level.
     * @param model_name Commercial chassis model name.
     * @param supported_form_factor Maximum supported motherboard form factor ("ATX", "Micro-ATX", "Mini-ITX").
     * @param max_gpu_length_mm Maximum graphics card length supported in millimeters.
     * @param max_cpu_cooler_height_mm Maximum tower CPU cooler height supported in millimeters.
     * @param dust_filter_clog_percentage Initial mesh filter clogging percentage (0.0 to 100.0).
     */
    explicit ComputerCase(const std::string& model_name = "Fractal Design Meshify 2", const std::string& supported_form_factor = "ATX", int max_gpu_length_mm = 450, int max_cpu_cooler_height_mm = 185, double dust_filter_clog_percentage = 0.0);

    /**
     * @brief Compares two computer cases for equality.
     * @param other ComputerCase instance to compare with.
     * @return true if model, clearances, form factor, and dust state match.
     */
    bool operator==(const ComputerCase& other) const;

    /**
     * @brief Inequality operator.
     * @param other ComputerCase instance to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const ComputerCase& other) const;

    /**
     * @brief Stream output operator for formatting PC case specifications.
     * @param os Output stream.
     * @param ccase ComputerCase instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ComputerCase& ccase);

    /**
     * @brief Checks whether a motherboard of the specified form factor fits inside the chassis.
     * @param mb_form_factor Motherboard form factor string ("ATX", "Micro-ATX", "Mini-ITX", "E-ATX").
     * @return true if compatible.
     */
    bool CheckMotherboardCompatibility(const std::string& mb_form_factor) const;

    /**
     * @brief Checks whether a discrete graphics card fits within the chassis length clearance.
     * @param gpu_length_mm Graphics card length in millimeters.
     * @return true if the GPU fits inside.
     */
    bool CheckGpuFit(int gpu_length_mm) const;

    /**
     * @brief Simulates environmental dust buildup on the intake mesh filters over time.
     * @param percentage Additional dust accumulation percentage.
     */
    void AccumulateDust(double percentage);

    /**
     * @brief Cleans all chassis mesh dust filters back to 0% clogging.
     */
    void CleanFilters();

    /**
     * @brief Gets chassis commercial model name.
     * @return Model name string reference.
     */
    const std::string& GetModelName() const;

    /**
     * @brief Gets maximum supported motherboard form factor.
     * @return Form factor string reference.
     */
    const std::string& GetSupportedFormFactor() const;

    /**
     * @brief Gets maximum supported graphics card length in millimeters.
     * @return Maximum GPU length in mm.
     */
    int GetMaxGpuLengthMm() const;

    /**
     * @brief Gets maximum supported CPU tower cooler height in millimeters.
     * @return Maximum cooler height in mm.
     */
    int GetMaxCpuCoolerHeightMm() const;

    /**
     * @brief Gets current dust filter clogging percentage.
     * @return Clog percentage (0.0 to 100.0).
     */
    double GetDustFilterClogPercentage() const;

private:
    std::string model_name_;
    std::string supported_form_factor_;
    int max_gpu_length_mm_;
    int max_cpu_cooler_height_mm_;
    double dust_filter_clog_percentage_;
};

#endif