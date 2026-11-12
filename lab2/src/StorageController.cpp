/**
 * @file StorageController.cpp
 * @brief Implementation of StorageController methods.
 * @author Nikita Momot
 * @date 2026
 */

#include <algorithm>
#include "StorageController.h"
#include "ComputerException.h"

StorageController::StorageController(const std::string& controller_type) : 
    controller_type_(controller_type), raid_mode_("NONE"), ssds_(), hdds_(), is_raid_healthy_(true) {}

bool StorageController::operator==(const StorageController& other) const {
    return (controller_type_ == other.controller_type_ &&
            raid_mode_ == other.raid_mode_ &&
            ssds_.size() == other.ssds_.size() &&
            hdds_.size() == other.hdds_.size());
}

bool StorageController::operator!=(const StorageController& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const StorageController& controller) {
    os << "Storage Controller [" << controller.controller_type_ << ", RAID: " << controller.raid_mode_ << ", SSDs: " << controller.ssds_.size() << ", HDDs: " << controller.hdds_.size() << ", Total Space: " << controller.GetTotalCapacityGb() << " GB]";
    return os;
}

void StorageController::AttachSSD(const SSD& drive) {
    ssds_.push_back(drive);
}

void StorageController::AttachHDD(const HDD& drive) {
    hdds_.push_back(drive);
}

void StorageController::ConfigureRAID(const std::string& mode) {
    if (mode != "NONE" && mode != "RAID0" && mode != "RAID1" && mode != "JBOD")
        throw ComputerException("Unsupported RAID mode requested: " + mode);
    
    int total_drives = static_cast<int>(ssds_.size() + hdds_.size());
    if ((mode == "RAID0" || mode == "RAID1") && total_drives < 2)
        throw ComputerException("RAID0 and RAID1 require at least two connected storage drives.");
    
    raid_mode_ = mode;
    is_raid_healthy_ = true;
}

double StorageController::GetTotalCapacityGb() const {
    double total = 0.0;
    for (const auto& ssd : ssds_)
        total += static_cast<double>(ssd.GetCapacityGb());
    
    for (const auto& hdd : hdds_)
        total += static_cast<double>(hdd.GetCapacityGb());

    if (raid_mode_ == "RAID1")
        return total / 2;

    return total;
}

bool StorageController::PerformIntegrityCheck() {
    bool all_ok = true;
    for (const auto& ssd : ssds_) {
        if (ssd.GetHealthPercentage() < 10)
            all_ok = false;
    }

    for (const auto& hdd : hdds_) {
        if (hdd.GetBadSectorsCount() > 50)
            all_ok = false;
    }

    is_raid_healthy_ = all_ok;
    return all_ok;
}

std::string StorageController::GetControllerType() const {
    return controller_type_;
}

std::string StorageController::GetRaidMode() const {
    return raid_mode_;
}

int StorageController::GetSsdCount() const {
    return static_cast<int>(ssds_.size());
}

int StorageController::GetHddCount() const {
    return static_cast<int>(hdds_.size());
}

bool StorageController::IsRaidHealthy() const {
    return is_raid_healthy_;
}