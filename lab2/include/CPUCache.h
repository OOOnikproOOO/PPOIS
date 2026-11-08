/**
 * @file CPUCache.h
 * @brief Declaration of the CPUCache class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef CPUCACHE_H
#define CPUCACHE_H

#include <iostream>

/**
 * @brief Class representing processor cache memory (L1, L2 or L3).
 */
class CPUCache {
public:
    /**
     * @brief Constructor of a CPU cache with specified level, size, and line size.
     * @param level Cache hierarchy level (1, 2 or 3).
     * @param size_kb Total cache capacity in kilobytes.
     * @param line_size_bytes Cache line size in bytes.
     */
    explicit CPUCache(int level = 1, int size_kb = 32, int line_size_bytes = 64);

    /**
     * @brief Equality operator comparing two cache instances.
     * @param other The cache to compare with.
     * @return true if level, size, line size and dirty state match.
     */
    bool operator==(const CPUCache& other) const;

    /**
     * @brief Inequality operator.
     * @param other The cache to compare with.
     * @return true if any core property differs.
     */
    bool operator!=(const CPUCache& other) const;

    /**
     * @brief Stream output operator for formatting cache status.
     * @param os Output stream.
     * @param cache Cache instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const CPUCache& cache);

    /**
     * @brief Simulates a cache read request.
     * @param address Target memory address.
     * @return true on cache hit, false on cache miss.
     */
    bool Read(long long address);

    /**
     * @brief Simulates writing data into the cache.
     * @param address Target memory address.
     * @param bytes Number of bytes to write.
     * @return true on successful write.
     */
    bool Write(long long address, int bytes);

    /**
     * @brief Flushes dirty cache lines back to the next memory hierarchy level.
     */
    void Flush();

    /**
     * @brief Invalidates all cache lines and resets hit/miss counters.
     */
    void Invalidate();

    /**
     * @brief Calculates cache hit rate as a ratio between 0.0 and 1.0.
     * @return Hit rate ratio (1.0 = 100% hits).
     */
    double GetHitRate() const;

    /**
     * @brief Gets cache level (1, 2 or 3).
     * @return Hierarchy level.
     */
    int GetLevel() const;

    /**
     * @brief Gets total cache capacity in kilobytes.
     * @return Capacity in KB.
     */
    int GetSizeKb() const;

    /**
     * @brief Gets cache line size in bytes.
     * @return Line size.
     */
    int GetLineSizeBytes() const;

    /**
     * @brief Gets total recorded cache hits.
     * @return Number of hits.
     */
    int GetHits() const;

    /**
     * @brief Gets total recorded cache misses.
     * @return Number of misses.
     */
    int GetMisses() const;

    /**
     * @brief Checks if cache contains unwritten dirty data.
     * @return true if dirty flag is active.
     */
    bool IsDirty() const;

private:
    int level_;
    int size_kb_;
    int line_size_bytes_;
    int hits_;
    int misses_;
    bool is_dirty_;
};

#endif