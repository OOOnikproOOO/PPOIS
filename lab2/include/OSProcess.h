/**
 * @file OSProcess.h
 * @brief Declaration of the OSProcess class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef OSPROCESS_H
#define OSPROCESS_H

#include <iostream>
#include <string>

/**
 * @brief Represents an operating system process with PID, memory footprint and execution state.
 */
class OSProcess {
public:
    /**
     * @brief Constructs an OSProcess instance.
     * @param pid Process identifier.
     * @param process_name Executable/process name.
     * @param memory_mb Initial allocated RAM in megabytes.
     * @param is_running Whether the process is currently running.
     */
    explicit OSProcess(int pid = 1, const std::string& process_name = "systemd", int memory_mb = 64, bool is_running = true);

    /**
     * @brief Equality operator comparing process attributes.
     * @param other Another OSProcess instance.
     * @return true if process attributes match.
     */
    bool operator==(const OSProcess& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another OSProcess instance.
     * @return true if processes differ.
     */
    bool operator!=(const OSProcess& other) const;

    /**
     * @brief Stream output operator for formatting process state.
     * @param os Output stream.
     * @param process OSProcess instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const OSProcess& process);

    /**
     * @brief Suspends execution of the process.
     */
    void Suspend();

    /**
     * @brief Resumes execution of a suspended process.
     */
    void Resume();

    /**
     * @brief Allocates additional RAM for the process.
     * @param delta_mb Memory to allocate in megabytes.
     */
    void AllocateMemory(int delta_mb);

    /**
     * @brief Releases allocated RAM held by the process.
     * @param delta_mb Memory to release in megabytes.
     */
    void FreeMemory(int delta_mb);

    /**
     * @brief Gets the process ID (PID).
     * @return Process ID.
     */
    int GetPid() const;

    /**
     * @brief Gets the process name.
     * @return Process name string.
     */
    const std::string& GetProcessName() const;

    /**
     * @brief Gets current process RAM usage in megabytes.
     * @return Memory usage in MB.
     */
    int GetMemoryMb() const;

    /**
     * @brief Checks whether the process is currently active/running.
     * @return true if running.
     */
    bool IsRunning() const;

private:
    int pid_;
    std::string process_name_;
    int memory_mb_;
    bool is_running_;
};

#endif