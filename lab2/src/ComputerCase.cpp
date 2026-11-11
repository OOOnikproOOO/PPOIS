/**
 * @file ComputerCase.cpp
 * @brief Implementation of ComputerCase methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ComputerCase.h"
#include "Exceptions.h"

ComputerCase::ComputerCase(const std::string& model_name, const std::string& supported_form_factor, int max_gpu_length_mm, int max_cpu_cooler_height_mm, double dust_filter_clog_percentage) :
    model_name_(model_name), supported_form_factor_(supported_form_factor), max_gpu_length_mm_(max_gpu_length_mm), max_cpu_cooler_height_mm_(max_cpu_cooler_height_mm), dust_filter_clog_percentage_(dust_filter_clog_percentage) {}

bool ComputerCase::operator==(const ComputerCase& other) const {
    return model_name_ == other.model_name_ && supported_form_factor_ == other.supported_form_factor_ &&
           max_gpu_length_mm_ == other.max_gpu_length_mm_ && max_cpu_cooler_height_mm_ == other.max_cpu_cooler_height_mm_ &&
           dust_filter_clog_percentage_ == other.dust_filter_clog_percentage_;
}

bool ComputerCase::operator!=(const ComputerCase& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const ComputerCase& ccase) {
    os << "ComputerCase " << ccase.model_name_ << " (" << ccase.supported_form_factor_ << ", max GPU: " << ccase.max_gpu_length_mm_ << "mm, max Cooler: " << ccase.max_cpu_cooler_height_mm_ << "mm, Dust: " << ccase.dust_filter_clog_percentage_ << "%)";
    return os;
}

bool ComputerCase::CheckMotherboardCompatibility(const std::string& mb_form_factor) const {
    if (supported_form_factor_ == "E-ATX") 
        return true;
    if (supported_form_factor_ == "ATX") 
        return mb_form_factor == "ATX" || mb_form_factor == "Micro-ATX" || mb_form_factor == "Mini-ITX";
    if (supported_form_factor_ == "Micro-ATX") 
        return mb_form_factor == "Micro-ATX" || mb_form_factor == "Mini-ITX";
    if (supported_form_factor_ == "Mini-ITX") 
        return mb_form_factor == "Mini-ITX";

    return false;
}

bool ComputerCase::CheckGpuFit(int gpu_length_mm) const {
    return gpu_length_mm > 0 && gpu_length_mm <= max_gpu_length_mm_;
}

void ComputerCase::AccumulateDust(double percentage) {
    if (percentage <= 0.0) 
        return;
    dust_filter_clog_percentage_ += percentage;
    if (dust_filter_clog_percentage_ > 100.0) 
        dust_filter_clog_percentage_ = 100.0;
    if (dust_filter_clog_percentage_ > 85.0) 
        throw ThermalThrottlingException("Dust filters severely clogged (> 85%). Airflow restricted.");
}

void ComputerCase::CleanFilters() {
    dust_filter_clog_percentage_ = 0.0;
}

const std::string& ComputerCase::GetModelName() const {
    return model_name_;
}

const std::string& ComputerCase::GetSupportedFormFactor() const {
    return supported_form_factor_;
}

int ComputerCase::GetMaxGpuLengthMm() const {
    return max_gpu_length_mm_;
}

int ComputerCase::GetMaxCpuCoolerHeightMm() const {
    return max_cpu_cooler_height_mm_;
}

double ComputerCase::GetDustFilterClogPercentage() const {
    return dust_filter_clog_percentage_;
}
