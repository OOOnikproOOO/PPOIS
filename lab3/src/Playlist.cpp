/**
 * @file Playlist.cpp
 * @brief Implementation of Playlist methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Playlist.h"
#include "PlaylistFullException.h"
#include "TrackNotFoundException.h"

Playlist::Playlist(const std::string& name, bool is_public, size_t max_capacity) :
    name_(name), is_public_(is_public), max_capacity_(max_capacity > 0 ? max_capacity : 500), tracks_() {}

bool Playlist::operator==(const Playlist& other) const {
    return name_ == other.name_ &&
           is_public_ == other.is_public_ &&
           max_capacity_ == other.max_capacity_ &&
           tracks_ == other.tracks_;
}

bool Playlist::operator!=(const Playlist& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "Playlist: " << playlist.name_ << " [" << playlist.tracks_.size() << "/" << playlist.max_capacity_ << " tracks, " << (playlist.is_public_ ? "Public" : "Private") << "]";
    return os;
}

void Playlist::AddTrack(const AudioTrack& track) {
    if (tracks_.size() >= max_capacity_)
        throw PlaylistFullException("Playlist '" + name_ + "' is full (limit: " + std::to_string(max_capacity_) + ").");
    
    tracks_.push_back(track);
}

void Playlist::RemoveTrack(size_t index) {
    if (index >= tracks_.size())
        throw TrackNotFoundException("Track index " + std::to_string(index) + " out of bounds in playlist '" + name_ + "'.");
    
    tracks_.erase(tracks_.begin() + index);
}

void Playlist::MoveTrack(size_t from_idx, size_t to_idx) {
    if (from_idx >= tracks_.size() || to_idx >= tracks_.size())
        throw TrackNotFoundException("Track move index out of bounds in playlist '" + name_ + "'.");
    
    if (from_idx == to_idx) 
        return;
    
    AudioTrack track = tracks_[from_idx];
    tracks_.erase(tracks_.begin() + from_idx);
    tracks_.insert(tracks_.begin() + to_idx, track);
}

double Playlist::CalculateTotalDurationSec() const {
    double total = 0.0;
    for (const auto& track : tracks_)
        total += track.GetDurationSec();
    
    return total;
}

void Playlist::Clear() {
    tracks_.clear();
}

const std::string& Playlist::GetName() const {
    return name_;
}

bool Playlist::IsPublic() const {
    return is_public_;
}

size_t Playlist::GetMaxCapacity() const {
    return max_capacity_;
}

const std::vector<AudioTrack>& Playlist::GetTracks() const {
    return tracks_;
}

size_t Playlist::GetTracksCount() const {
    return tracks_.size();
}