/**
 * @file PlaybackHistory.cpp
 * @brief Implementation of PlaybackHistory methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PlaybackHistory.h"
#include <algorithm>

PlaybackHistory::PlaybackHistory(size_t max_entries) :
    max_entries_(max_entries > 0 ? max_entries : 50), history_records_(), total_played_count_(0) {}

bool PlaybackHistory::operator==(const PlaybackHistory& other) const {
    return max_entries_ == other.max_entries_ &&
           history_records_ == other.history_records_ &&
           total_played_count_ == other.total_played_count_;
}

bool PlaybackHistory::operator!=(const PlaybackHistory& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PlaybackHistory& history) {
    os << "History[" << history.history_records_.size() << "/" << history.max_entries_ << " logged, Total played: " << history.total_played_count_ << "]";
    return os;
}

void PlaybackHistory::RecordTrack(const std::string& track_title) {
    if (history_records_.size() >= max_entries_)
        history_records_.erase(history_records_.begin());
    
    history_records_.push_back(track_title);
    total_played_count_++;
}

std::vector<std::string> PlaybackHistory::GetRecentTracks(size_t count) const {
    std::vector<std::string> recent;
    if (history_records_.empty() || count == 0)
        return recent;
    
    size_t take = std::min(count, history_records_.size());
    for (size_t i = 0; i < take; i++)
        recent.push_back(history_records_[history_records_.size() - 1 - i]);
    
    return recent;
}

bool PlaybackHistory::ContainsRecord(const std::string& track_title) const {
    return std::find(history_records_.begin(), history_records_.end(), track_title) != history_records_.end();
}

void PlaybackHistory::ClearHistory() {
    history_records_.clear();
}

size_t PlaybackHistory::GetMaxEntries() const {
    return max_entries_;
}

size_t PlaybackHistory::GetEntriesCount() const {
    return history_records_.size();
}

int PlaybackHistory::GetTotalPlayedCount() const {
    return total_played_count_;
}

const std::vector<std::string>& PlaybackHistory::GetRecords() const {
    return history_records_;
}