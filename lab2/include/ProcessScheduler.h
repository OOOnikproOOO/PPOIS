/**
 * @file ProcessScheduler.h
 * @brief Declaration of the ProcessScheduler class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PROCESSSCHEDULER_H
#define PROCESSSCHEDULER_H

#include <iostream>
#include <string>
#include <vector>
#include "OSProcess.h"

/**
 * @brief Represents the OS kernel process scheduler tracking active and suspended tasks.
 */
class ProcessScheduler {
public:
    /**
     * @brief Constructs a ProcessScheduler instance.
     * @param policy Scheduling algorithm name (e.g., "CFS", "RoundRobin").
     * @param max_processes Maximum allowed concurrent processes.
     */
    explicit ProcessScheduler(const std::string& policy = "CFS", int max_processes = 64);

    /**
     * @brief Equality operator comparing scheduler policy, limits, and process list.
     * @param other Another ProcessScheduler instance.
     * @return true if schedulers match.
     */
    bool operator==(const ProcessScheduler& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another ProcessScheduler instance.
     * @return true if schedulers differ.
     */
    bool operator!=(const ProcessScheduler& other) const;

    /**
     * @brief Stream output operator for formatting scheduler summary.
     * @param os Output stream.
     * @param scheduler ProcessScheduler instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ProcessScheduler& scheduler);

    /**
     * @brief Launches and registers a new process in the scheduler queue.
     * @param process OSProcess instance to launch.
     */
    void LaunchProcess(const OSProcess& process);

    /**
     * @brief Terminates and removes a process by PID.
     * @param pid Target process identifier.
     */
    void TerminateProcess(int pid);

    /**
     * @brief Calculates total RAM consumed by all tracked processes in megabytes.
     * @return Total memory usage in MB.
     */
    int CalculateTotalMemoryUsageMb() const;

    /**
     * @brief Counts how many processes are currently in the running state.
     * @return Running process count.
     */
    int CountRunningProcesses() const;

    /**
     * @brief Gets scheduling policy algorithm name.
     * @return Policy name string.
     */
    const std::string& GetPolicy() const;

    /**
     * @brief Gets maximum supported concurrent processes.
     * @return Maximum process limit.
     */
    int GetMaxProcesses() const;

    /**
     * @brief Gets total number of registered processes.
     * @return Process count.
     */
    int GetProcessCount() const;

    /**
     * @brief Gets reference to a process by index.
     * @param index Process list index.
     * @return Reference to OSProcess.
     */
    OSProcess& GetProcess(int index);
    const OSProcess& GetProcess(int index) const;

private:
    std::string policy_;
    int max_processes_;
    std::vector<OSProcess> processes_;
};

#endif