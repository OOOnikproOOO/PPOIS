/**
 * @file ShuffleEngine.cpp
 * @brief Implementation of ShuffleEngine methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ShuffleEngine.h"
#include <numeric>
#include <algorithm>

ShuffleEngine::ShuffleEngine(unsigned int seed, bool is_enabled) :
    seed_(seed), is_enabled_(is_enabled), shuffled_order_() {}

bool ShuffleEngine::operator==(const ShuffleEngine& other) const {
    return seed_ == other.seed_ &&
           is_enabled_ == other.is_enabled_ &&
           shuffled_order_ == other.shuffled_order_;
}

bool ShuffleEngine::operator!=(const ShuffleEngine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const ShuffleEngine& engine) {
    os << "ShuffleEngine[" << (engine.is_enabled_ ? "ON" : "OFF") << ", Tracks: " << engine.shuffled_order_.size() << "]";
    return os;
}

void ShuffleEngine::GenerateShuffle(size_t total_tracks) {
    shuffled_order_.clear();
    if (total_tracks == 0)
        return;
    
    shuffled_order_.resize(total_tracks);
    std::iota(shuffled_order_.begin(), shuffled_order_.end(), 0);

    unsigned int current_seed = seed_;
    for (size_t i = total_tracks - 1; i > 0; i--) {
        current_seed = (current_seed * 1103515245 + 12345) & 0x7fffffff;
        size_t j = current_seed % (i + 1);
        std::swap(shuffled_order_[i], shuffled_order_[j]);
    }
}

size_t ShuffleEngine::GetNextShuffledIndex(size_t step) const {
    if (shuffled_order_.empty())
        return 0;
    
    return shuffled_order_[step % shuffled_order_.size()];
}

void ShuffleEngine::Reset() {
    shuffled_order_.clear();
}

void ShuffleEngine::ToggleShuffle(bool enable) {
    is_enabled_ = enable;
}

unsigned int ShuffleEngine::GetSeed() const {
    return seed_;
}

bool ShuffleEngine::IsEnabled() const {
    return is_enabled_;
}

size_t ShuffleEngine::GetShuffledSize() const {
    return shuffled_order_.size();
}

const std::vector<size_t>& ShuffleEngine::GetShuffledOrder() const {
    return shuffled_order_;
}