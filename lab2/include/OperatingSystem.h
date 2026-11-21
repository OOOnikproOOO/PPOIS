/**
 * @file OperatingSystem.h
 * @brief Declaration of the OperatingSystem class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include "Bootloader.h"
#include "DeviceDriver.h"
#include "FileSystem.h"
#include "ProcessScheduler.h"
#include "SystemClock.h"

/**
 * @brief Represents the operating system orchestrating firmware boot, file system, process scheduling and drivers.
 */
class OperatingSystem {
public:
    /**
     * @brief Constructs an OperatingSystem instance.
     * @param os_name Operating system name and release.
     * @param bootloader Associated Bootloader instance.
     * @param file_system Associated FileSystem instance.
     * @param scheduler Associated ProcessScheduler instance.
     * @param clock Associated SystemClock instance.
     */
    explicit OperatingSystem(const std::string& os_name = "Ubuntu Linux 24.04 LTS", const Bootloader& bootloader = Bootloader(), const FileSystem& file_system = FileSystem(), const ProcessScheduler& scheduler = ProcessScheduler(), const SystemClock& clock = SystemClock());

    /**
     * @brief Equality operator comparing OS state and core subsystems.
     * @param other Another OperatingSystem instance.
     * @return true if OS instances match.
     */
    bool operator==(const OperatingSystem& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another OperatingSystem instance.
     * @return true if OS instances differ.
     */
    bool operator!=(const OperatingSystem& other) const;

    /**
     * @brief Stream output operator for formatting OS status summary.
     * @param os Output stream.
     * @param system OperatingSystem instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const OperatingSystem& system);

    /**
     * @brief Verifies firmware/bootloader, loads drivers and boots the operating system.
     */
    void Boot();

    /**
     * @brief Unloads drivers and shuts down the operating system cleanly.
     */
    void Shutdown();

    /**
     * @brief Registers a kernel device driver with the OS.
     * @param driver DeviceDriver instance to register.
     */
    void RegisterDriver(const DeviceDriver& driver);

    /**
     * @brief Advances system uptime clock when the OS is booted.
     * @param seconds Elapsed seconds to advance.
     */
    void AdvanceUptime(long long seconds);

    /**
     * @brief Gets operating system name.
     * @return OS name string.
     */
    const std::string& GetOsName() const;

    /**
     * @brief Checks whether the OS is currently booted and running.
     * @return true if booted.
     */
    bool IsBooted() const;

    /**
     * @brief Gets count of registered device drivers.
     * @return Driver count.
     */
    int GetDriverCount() const;

    /**
     * @brief Gets reference to the system bootloader.
     * @return Reference to Bootloader.
     */
    Bootloader& GetBootloader();
    const Bootloader& GetBootloader() const;

    /**
     * @brief Gets reference to the OS file system.
     * @return Reference to FileSystem.
     */
    FileSystem& GetFileSystem();
    const FileSystem& GetFileSystem() const;

    /**
     * @brief Gets reference to the process scheduler.
     * @return Reference to ProcessScheduler.
     */
    ProcessScheduler& GetScheduler();
    const ProcessScheduler& GetScheduler() const;

    /**
     * @brief Gets reference to the system uptime clock.
     * @return Reference to SystemClock.
     */
    SystemClock& GetClock();
    const SystemClock& GetClock() const;

    /**
     * @brief Gets reference to a registered device driver by index.
     * @param index Driver index.
     * @return Reference to DeviceDriver.
     */
    DeviceDriver& GetDriver(int index);
    const DeviceDriver& GetDriver(int index) const;

private:
    std::string os_name_;
    bool is_booted_;
    Bootloader bootloader_;
    FileSystem file_system_;
    ProcessScheduler scheduler_;
    SystemClock clock_;
    std::vector<DeviceDriver> drivers_;
};

#endif