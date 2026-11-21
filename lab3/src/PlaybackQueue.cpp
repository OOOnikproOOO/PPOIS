/**
 * @file PlaybackQueue.cpp
 * @brief Implementation of PlaybackQueue methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PlaybackQueue.h"
#include "TrackNotFoundException.h"

PlaybackQueue::PlaybackQueue(size_t max_queue_size, bool auto_advance) :
    current_index_(-1), tracks_(), auto_advance_(auto_advance), max_queue_size_(max_queue_size > 0 ? max_queue_size : 100) {}

bool PlaybackQueue::operator==(const PlaybackQueue& other) const {
    return current_index_ == other.current_index_ &&
           tracks_ == other.tracks_ &&
           auto_advance_ == other.auto_advance_ &&
           max_queue_size_ == other.max_queue_size_;
}

bool PlaybackQueue::operator!=(const PlaybackQueue& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PlaybackQueue& queue) {
    os << "Queue[" << queue.tracks_.size() << "/" << queue.max_queue_size_ << " tracks, CurrentIndex: " << queue.current_index_ << "]";
    return os;
}

bool PlaybackQueue::Enqueue(const AudioTrack& track) {
    if (tracks_.size() >= max_queue_size_)
        return false;
    
    tracks_.push_back(track);
    if (current_index_ < 0)
        current_index_ = 0;
    
    return true;
}

bool PlaybackQueue::NextTrack() {
    if (tracks_.empty())
        return false;
    
    if (current_index_ + 1 < static_cast<int>(tracks_.size())) {
        current_index_++;
        return true;
    }
    return false;
}

bool PlaybackQueue::PreviousTrack() {
    if (tracks_.empty())
        return false;
    
    if (current_index_ > 0) {
        current_index_--;
        return true;
    }
    return false;
}

const AudioTrack& PlaybackQueue::GetCurrentTrack() const {
    if (current_index_ < 0 || current_index_ >= static_cast<int>(tracks_.size()))
        throw TrackNotFoundException("No active track selected in playback queue.");
    
    return tracks_[current_index_];
}

void PlaybackQueue::RemoveAt(size_t index) {
    if (index >= tracks_.size())
        return;
    
    tracks_.erase(tracks_.begin() + index);
    if (tracks_.empty())
        current_index_ = -1;
    else if (current_index_ >= static_cast<int>(tracks_.size()))
        current_index_ = static_cast<int>(tracks_.size()) - 1;
}

void PlaybackQueue::ClearQueue() {
    tracks_.clear();
    current_index_ = -1;
}

int PlaybackQueue::GetCurrentIndex() const {
    return current_index_;
}

size_t PlaybackQueue::GetQueueSize() const {
    return tracks_.size();
}

bool PlaybackQueue::IsAutoAdvance() const {
    return auto_advance_;
}

const std::vector<AudioTrack>& PlaybackQueue::GetTracks() const {
    return tracks_;
}