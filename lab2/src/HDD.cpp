/**
 * @file HDD.cpp
 * @brief Implementation of HDD methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "HDD.h"
#include "StorageOutOfSpaceException.h"
#include "StorageBadSectorException.h"

HDD::HDD(const std::string& model, int rpm, int capacity_gb, int cache_mb) :
    model_(model), rpm_(rpm), capacity_gb_(capacity_gb), used_gb_(0), cache_mb_(cache_mb), heads_parked_(true), bad_sectors_count_(0) {}

bool HDD::operator==(const HDD& other) const {
    return (model_ == other.model_ &&
            rpm_ == other.rpm_ &&
            capacity_gb_ == other.capacity_gb_);
}

bool HDD::operator!=(const HDD& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const HDD& hdd) {
    os << "HDD: " << hdd.model_ << " [" << hdd.rpm_ << " RPM, " << hdd.used_gb_ << "/" << hdd.capacity_gb_ << " GB, Cache: " << hdd.cache_mb_ << " MB, Parked: " << (hdd.heads_parked_ ? "Yes" : "No") << ", Bad Sectors: " << hdd.bad_sectors_count_ << "]";
    return os;
}

void HDD::ParkHeads() {
    heads_parked_ = true;
}

void HDD::SpinUp() {
    heads_parked_ = false;
}

bool HDD::WriteData(double gigabytes) {
    if (gigabytes <= 0.0)
        return false;
    
    if (heads_parked_)
        SpinUp();
    
    if (bad_sectors_count_ >= 100)
        throw StorageBadSectorException("HDD has too many bad sectors; write operation aborted.");
    
    if (used_gb_ + static_cast<int>(gigabytes) > capacity_gb_)
        throw StorageOutOfSpaceException("HDD has insufficient disk space for write request.");
    
    used_gb_ += static_cast<int>(gigabytes);
    return true;
}

bool HDD::ReadData(double gigabytes) {
    if (heads_parked_)
        SpinUp();
    
    return (gigabytes > 0.0 && gigabytes <= static_cast<double>(used_gb_));
}

void HDD::ScanForBadSectors(int scanned_sectors) {
    if (scanned_sectors > 100000)
        bad_sectors_count_ += (scanned_sectors / 100000);
}

std::string HDD::GetModel() const {
    return model_;
}

int HDD::GetRpm() const {
    return rpm_;
}

int HDD::GetCapacityGb() const {
    return capacity_gb_;
}

int HDD::GetUsedGb() const {
    return used_gb_;
}

int HDD::GetFreeSpaceGb() const {
    return capacity_gb_ - used_gb_;
}

int HDD::GetCacheMb() const {
    return cache_mb_;
}

bool HDD::AreHeadsParked() const {
    return heads_parked_;
}

int HDD::GetBadSectorsCount() const {
    return bad_sectors_count_;
}