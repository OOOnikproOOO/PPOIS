/**
 * @file OperatingSystem.cpp
 * @brief Implementation of OperatingSystem methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "OperatingSystem.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

OperatingSystem::OperatingSystem(const std::string& os_name, const Bootloader& bootloader, const FileSystem& file_system, const ProcessScheduler& scheduler, const SystemClock& clock) :
    os_name_(os_name), is_booted_(false), bootloader_(bootloader), file_system_(file_system), scheduler_(scheduler), clock_(clock) {}

bool OperatingSystem::operator==(const OperatingSystem& other) const {
    return os_name_ == other.os_name_ && is_booted_ == other.is_booted_ &&
           bootloader_ == other.bootloader_ && file_system_ == other.file_system_ &&
           scheduler_ == other.scheduler_ && clock_ == other.clock_ && drivers_ == other.drivers_;
}

bool OperatingSystem::operator!=(const OperatingSystem& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const OperatingSystem& system) {
    os << "OS '" << system.os_name_ << "' [" << (system.is_booted_ ? "Booted" : "Halted") << ", Drivers: " << system.drivers_.size() << ", " << system.scheduler_ << "]";
    return os;
}

void OperatingSystem::Boot() {
    bootloader_.VerifyAndLoadKernel();
    for (int i = 0; i < drivers_.size(); i++)
        drivers_[i].Load();
    clock_.SyncWithNtp();
    is_booted_ = true;
}

void OperatingSystem::Shutdown() {
    for (int i = 0; i < drivers_.size(); i++)
        drivers_[i].Unload();
    is_booted_ = false;
}

void OperatingSystem::RegisterDriver(const DeviceDriver& driver) {
    if (driver.GetDriverName().empty()) 
        throw ComputerException("Driver name cannot be empty.");
    drivers_.push_back(driver);
}

void OperatingSystem::AdvanceUptime(long long seconds) {
    if (!is_booted_) 
        throw ComputerException("Cannot advance uptime while operating system is shut down.");
    clock_.Tick(seconds);
}

const std::string& OperatingSystem::GetOsName() const {
    return os_name_;
}

bool OperatingSystem::IsBooted() const {
    return is_booted_;
}

int OperatingSystem::GetDriverCount() const {
    return static_cast<int>(drivers_.size());
}

Bootloader& OperatingSystem::GetBootloader() {
    return bootloader_;
}

const Bootloader& OperatingSystem::GetBootloader() const {
    return bootloader_;
}

FileSystem& OperatingSystem::GetFileSystem() {
    return file_system_;
}

const FileSystem& OperatingSystem::GetFileSystem() const {
    return file_system_;
}

ProcessScheduler& OperatingSystem::GetScheduler() {
    return scheduler_;
}

const ProcessScheduler& OperatingSystem::GetScheduler() const {
    return scheduler_;
}

SystemClock& OperatingSystem::GetClock() {
    return clock_;
}

const SystemClock& OperatingSystem::GetClock() const {
    return clock_;
}

DeviceDriver& OperatingSystem::GetDriver(int index) {
    if (index < 0 || index >= drivers_.size()) 
        throw DeviceNotFoundException("Device driver index out of range.");
    return drivers_[index];
}

const DeviceDriver& OperatingSystem::GetDriver(int index) const {
    if (index < 0 || index >= drivers_.size()) 
        throw DeviceNotFoundException("Device driver index out of range.");
    return drivers_[index];
}