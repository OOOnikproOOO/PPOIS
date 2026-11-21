/**
 * @file SystemBenchmark.cpp
 * @brief Implementation of SystemBenchmark methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SystemBenchmark.h"

SystemBenchmark::SystemBenchmark(int cpu_score, int gpu_score, int memory_score, int storage_score) :
    cpu_score_(cpu_score), gpu_score_(gpu_score), memory_score_(memory_score), storage_score_(storage_score), total_score_(0) {
    total_score_ = CalculateTotalScore();
}

bool SystemBenchmark::operator==(const SystemBenchmark& other) const {
    return cpu_score_ == other.cpu_score_ && gpu_score_ == other.gpu_score_ &&
           memory_score_ == other.memory_score_ && storage_score_ == other.storage_score_ &&
           total_score_ == other.total_score_;
}

bool SystemBenchmark::operator!=(const SystemBenchmark& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SystemBenchmark& benchmark) {
    os << "Benchmark [Total: " << benchmark.CalculateTotalScore() << " pts | CPU: " << benchmark.cpu_score_ << ", GPU: " << benchmark.gpu_score_ << ", RAM: " << benchmark.memory_score_ << ", Disk: " << benchmark.storage_score_ << "]";
    return os;
}

void SystemBenchmark::BenchmarkCpu(int cores, int clock_mhz) {
    cpu_score_ = static_cast<int>(cores * (clock_mhz / 100.0) * 15);
    total_score_ = CalculateTotalScore();
}

void SystemBenchmark::BenchmarkGpu(int clock_mhz, int vram_mb) {
    gpu_score_ = static_cast<int>((clock_mhz / 50.0) * (vram_mb / 1024) * 20);
    total_score_ = CalculateTotalScore();
}

void SystemBenchmark::BenchmarkMemory(int capacity_mb, int frequency_mhz) {
    memory_score_ = static_cast<int>((capacity_mb / 1024.0) * (frequency_mhz / 200) * 12);
    total_score_ = CalculateTotalScore();
}

void SystemBenchmark::BenchmarkStorage(int capacity_gb, bool is_ssd) {
    storage_score_ = static_cast<int>((capacity_gb / 100.0) * (is_ssd ? 250 : 40));
    total_score_ = CalculateTotalScore();
}

int SystemBenchmark::GetCpuScore() const {
    return cpu_score_;
}

int SystemBenchmark::GetGpuScore() const {
    return gpu_score_;
}

int SystemBenchmark::GetMemoryScore() const {
    return memory_score_;
}

int SystemBenchmark::GetStorageScore() const {
    return storage_score_;
}

int SystemBenchmark::GetTotalScore() const {
    return CalculateTotalScore();
}

int SystemBenchmark::CalculateTotalScore() const {
    return cpu_score_ + gpu_score_ + memory_score_ + storage_score_;
}