/**
 * @file CPUCache.cpp
 * @brief Implementation of CPUCache.
 * @author Nikita Momot
 * @date 2026
 */

#include "CPUCache.h"

CPUCache::CPUCache(int level, int size_kb, int line_size_bytes) : 
    level_(level), size_kb_(size_kb), line_size_bytes_(line_size_bytes), hits_(0), misses_(0), is_dirty_(false) {}

bool CPUCache::operator==(const CPUCache& other) const {
    return (level_ == other.level_ &&
            size_kb_ == other.size_kb_ &&
            line_size_bytes_ == other.line_size_bytes_ &&
            is_dirty_ == other.is_dirty_);
}

bool CPUCache::operator!=(const CPUCache& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CPUCache& cache) {
    os << "L" << cache.level_ << " Cache [" << cache.size_kb_ << " KB, Line: " << cache.line_size_bytes_ << " B, Hits: " << cache.hits_ << ", Misses: " << cache.misses_ << "]";
    return os;
}

bool CPUCache::Read(long long address) {
    const long long block_mask = 0x7FLL;
    bool hit = ((address & block_mask) != 0LL);
    if (hit)
        hits_++;
    else
        misses_++;

    return hit;
}

bool CPUCache::Write(long long address, int bytes) {
    if (bytes <= 0)
        return false;
 
    Read(address);
    is_dirty_ = true;
    return true;
}

void CPUCache::Flush() {
    is_dirty_ = false;
}

void CPUCache::Invalidate() {
    hits_ = 0;
    misses_ = 0;
    is_dirty_ = false;
}

double CPUCache::GetHitRate() const {
    int total = hits_ + misses_;
    if (total == 0)
        return 0.0;

    return static_cast<double>(hits_) / total;
}

int CPUCache::GetLevel() const {
    return level_;
}

int CPUCache::GetSizeKb() const {
    return size_kb_;
}

int CPUCache::GetLineSizeBytes() const {
    return line_size_bytes_;
}

int CPUCache::GetHits() const {
    return hits_;
}

int CPUCache::GetMisses() const {
    return misses_;
}

bool CPUCache::IsDirty() const {
    return is_dirty_;
}