/**
 * @file SystemBenchmark.h
 * @brief Declaration of the SystemBenchmark class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef SYSTEMBENCHMARK_H
#define SYSTEMBENCHMARK_H

#include <iostream>

/**
 * @brief Represents a hardware performance benchmark suite scoring CPU, GPU, memory and storage.
 */
class SystemBenchmark {
public:
    /**
     * @brief Constructs a SystemBenchmark instance.
     * @param cpu_score Initial CPU benchmark score.
     * @param gpu_score Initial GPU 3D benchmark score.
     * @param memory_score Initial RAM throughput score.
     * @param storage_score Initial storage I/O score.
     */
    explicit SystemBenchmark(int cpu_score = 0, int gpu_score = 0, int memory_score = 0, int storage_score = 0);

    /**
     * @brief Equality operator comparing benchmark scores.
     * @param other Another SystemBenchmark instance.
     * @return true if scores match.
     */
    bool operator==(const SystemBenchmark& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another SystemBenchmark instance.
     * @return true if scores differ.
     */
    bool operator!=(const SystemBenchmark& other) const;

    /**
     * @brief Stream output operator for formatting benchmark results.
     * @param os Output stream.
     * @param benchmark SystemBenchmark instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const SystemBenchmark& benchmark);

    /**
     * @brief Runs CPU computational benchmark and evaluates score.
     * @param cores Physical core count.
     * @param clock_mhz Clock frequency in MHz.
     */
    void BenchmarkCpu(int cores, int clock_mhz);

    /**
     * @brief Runs GPU 3D rendering benchmark and evaluates score.
     * @param clock_mhz Core clock frequency in MHz.
     * @param vram_mb Video memory capacity in MB.
     */
    void BenchmarkGpu(int clock_mhz, int vram_mb);

    /**
     * @brief Runs memory bandwidth benchmark and evaluates score.
     * @param capacity_mb RAM capacity in MB.
     * @param frequency_mhz RAM frequency in MHz.
     */
    void BenchmarkMemory(int capacity_mb, int frequency_mhz);

    /**
     * @brief Runs storage read/write benchmark and evaluates score.
     * @param capacity_gb Storage capacity in GB.
     * @param is_ssd Whether storage medium is solid state drive.
     */
    void BenchmarkStorage(int capacity_gb, bool is_ssd);

    /**
     * @brief Gets CPU benchmark score.
     * @return CPU score.
     */
    int GetCpuScore() const;

    /**
     * @brief Gets GPU benchmark score.
     * @return GPU score.
     */
    int GetGpuScore() const;

    /**
     * @brief Gets memory benchmark score.
     * @return Memory score.
     */
    int GetMemoryScore() const;

    /**
     * @brief Gets storage benchmark score.
     * @return Storage score.
     */
    int GetStorageScore() const;

    /**
     * @brief Gets total overall benchmark score.
     * @return Total score.
     */
    int GetTotalScore() const;

private:
    /**
     * @brief Calculates composite total benchmark score.
     * @return Total benchmark points.
     */
    int CalculateTotalScore() const;

    int cpu_score_;
    int gpu_score_;
    int memory_score_;
    int storage_score_;
    int total_score_;
};

#endif