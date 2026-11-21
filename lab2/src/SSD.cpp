/**
 * @file SSD.cpp
 * @brief Implementation of SSD methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SSD.h"
#include "StorageOutOfSpaceException.h"

SSD::SSD(const std::string& model, const std::string& interface_type, int capacity_gb, double tbw_resource_tb) :
    model_(model), interface_type_(interface_type), capacity_gb_(capacity_gb), used_gb_(0), tbw_resource_tb_(tbw_resource_tb), tbw_written_tb_(0.0), health_percentage_(100) {}

bool SSD::operator==(const SSD& other) const {
    return (model_ == other.model_ &&
            interface_type_ == other.interface_type_ &&
            capacity_gb_ == other.capacity_gb_);
}

bool SSD::operator!=(const SSD& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SSD& ssd) {
    os << "SSD: " << ssd.model_ << " [" << ssd.interface_type_ << ", " << ssd.used_gb_ << "/" << ssd.capacity_gb_ << " GB, Health: " << ssd.health_percentage_ << "%, TBW: " << ssd.tbw_written_tb_ << "/" << ssd.tbw_resource_tb_ << " TB]";
    return os;
}

bool SSD::WriteData(double gigabytes) {
    if (gigabytes <= 0.0)
        return false;
    
    if (used_gb_ + static_cast<int>(gigabytes) > capacity_gb_)
        throw StorageOutOfSpaceException("SSD has insufficient free space for write request.");
    
    used_gb_ += static_cast<int>(gigabytes);
    tbw_written_tb_ += (gigabytes / 1024);
    RunHealthCheck();
    return true;
}

bool SSD::ReadData(double gigabytes) {
    return (gigabytes > 0.0 && gigabytes <= static_cast<double>(used_gb_));
}

void SSD::PerformTrim() {
    if (used_gb_ > 5)
        used_gb_ -= 2;
}

void SSD::RunHealthCheck() {
    if (tbw_resource_tb_ <= 0.0) {
        health_percentage_ = 0;
        return;
    }
    double wear_ratio = tbw_written_tb_ / tbw_resource_tb_;
    int remaining = static_cast<int>(100 * (1.0 - wear_ratio));
    if (remaining < 0)
        remaining = 0;
    
    health_percentage_ = remaining;
}

double SSD::EstimateRemainingLifespanMonths(double avg_write_gb_per_day) const {
    if (avg_write_gb_per_day <= 0.0)
        return 120.0;
    
    double remaining_tb = tbw_resource_tb_ - tbw_written_tb_;
    if (remaining_tb <= 0.0)
        return 0.0;
    
    double daily_tb = avg_write_gb_per_day / 1024;
    double days_left = remaining_tb / daily_tb;
    return days_left / 30.4;
}

std::string SSD::GetModel() const {
    return model_;
}

std::string SSD::GetInterfaceType() const {
    return interface_type_;
}

int SSD::GetCapacityGb() const {
    return capacity_gb_;
}

int SSD::GetUsedGb() const {
    return used_gb_;
}

int SSD::GetFreeSpaceGb() const {
    return capacity_gb_ - used_gb_;
}

double SSD::GetTbwResourceTb() const {
    return tbw_resource_tb_;
}

double SSD::GetTbwWrittenTb() const {
    return tbw_written_tb_;
}

int SSD::GetHealthPercentage() const {
    return health_percentage_;
}