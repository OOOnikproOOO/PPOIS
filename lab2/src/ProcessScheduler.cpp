/**
 * @file ProcessScheduler.cpp
 * @brief Implementation of ProcessScheduler methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ProcessScheduler.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"
#include "MemoryAllocationException.h"

ProcessScheduler::ProcessScheduler(const std::string& policy, int max_processes) :
    policy_(policy), max_processes_(max_processes) {}

bool ProcessScheduler::operator==(const ProcessScheduler& other) const {
    return policy_ == other.policy_ && max_processes_ == other.max_processes_ && processes_ == other.processes_;
}

bool ProcessScheduler::operator!=(const ProcessScheduler& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const ProcessScheduler& scheduler) {
    os << "ProcessScheduler [" << scheduler.policy_ << ", Processes: " << scheduler.processes_.size() << " / " << scheduler.max_processes_ << ", RAM: " << scheduler.CalculateTotalMemoryUsageMb() << " MB]";
    return os;
}

void ProcessScheduler::LaunchProcess(const OSProcess& process) {
    if (processes_.size() >= max_processes_) 
        throw MemoryAllocationException("Maximum concurrent process limit reached.");
    for (int i = 0; i < processes_.size(); i++) {
        if (processes_[i].GetPid() == process.GetPid()) 
            throw ComputerException("Process with PID " + std::to_string(process.GetPid()) + " already exists.");
    }
    processes_.push_back(process);
}

void ProcessScheduler::TerminateProcess(int pid) {
    for (int i = 0; i < processes_.size(); i++) {
        if (processes_[i].GetPid() == pid) {
            processes_.erase(processes_.begin() + i);
            return;
        }
    }
    throw DeviceNotFoundException("Process with PID " + std::to_string(pid) + " not found.");
}

int ProcessScheduler::CalculateTotalMemoryUsageMb() const {
    int total = 0;
    for (int i = 0; i < processes_.size(); i++)
        total += processes_[i].GetMemoryMb();
    return total;
}

int ProcessScheduler::CountRunningProcesses() const {
    int running = 0;
    for (int i = 0; i < processes_.size(); i++) {
        if (processes_[i].IsRunning()) 
            running++;
    }
    return running;
}

const std::string& ProcessScheduler::GetPolicy() const {
    return policy_;
}

int ProcessScheduler::GetMaxProcesses() const {
    return max_processes_;
}

int ProcessScheduler::GetProcessCount() const {
    return static_cast<int>(processes_.size());
}

OSProcess& ProcessScheduler::GetProcess(int index) {
    if (index < 0 || index >= processes_.size()) 
        throw DeviceNotFoundException("Process index out of range.");
    return processes_[index];
}

const OSProcess& ProcessScheduler::GetProcess(int index) const {
    if (index < 0 || index >= processes_.size()) 
        throw DeviceNotFoundException("Process index out of range.");
    return processes_[index];
}