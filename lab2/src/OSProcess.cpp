/**
 * @file OSProcess.cpp
 * @brief Implementation of OSProcess methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "OSProcess.h"
#include "MemoryAllocationException.h"

OSProcess::OSProcess(int pid, const std::string& process_name, int memory_mb, bool is_running) :
    pid_(pid), process_name_(process_name), memory_mb_(memory_mb), is_running_(is_running) {}

bool OSProcess::operator==(const OSProcess& other) const {
    return pid_ == other.pid_ && process_name_ == other.process_name_ &&
           memory_mb_ == other.memory_mb_ && is_running_ == other.is_running_;
}

bool OSProcess::operator!=(const OSProcess& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const OSProcess& process) {
    os << "PID " << process.pid_ << " '" << process.process_name_ << "' (" << process.memory_mb_ << " MB, " << (process.is_running_ ? "Running" : "Suspended") << ")";
    return os;
}

void OSProcess::Suspend() {
    is_running_ = false;
}

void OSProcess::Resume() {
    is_running_ = true;
}

void OSProcess::AllocateMemory(int delta_mb) {
    if (delta_mb <= 0) 
        throw MemoryAllocationException("Memory allocation delta must be positive.");
    memory_mb_ += delta_mb;
}

void OSProcess::FreeMemory(int delta_mb) {
    if (delta_mb <= 0) 
        return;
    memory_mb_ -= delta_mb;
    if (memory_mb_ < 0) 
        memory_mb_ = 0;
}

int OSProcess::GetPid() const {
    return pid_;
}

const std::string& OSProcess::GetProcessName() const {
    return process_name_;
}

int OSProcess::GetMemoryMb() const {
    return memory_mb_;
}

bool OSProcess::IsRunning() const {
    return is_running_;
}