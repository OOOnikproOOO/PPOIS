/**
 * @file Album.cpp
 * @brief Implementation of Album methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Album.h"
#include "TrackNotFoundException.h"

Album::Album(const std::string& title, int release_year, const std::string& record_label) : 
    title_(title), release_year_(release_year), record_label_(record_label), tracks_() {}

bool Album::operator==(const Album& other) const {
    return title_ == other.title_ &&
           release_year_ == other.release_year_ &&
           record_label_ == other.record_label_ &&
           tracks_ == other.tracks_;
}

bool Album::operator!=(const Album& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Album& album) {
    os << "Album: " << album.title_ << " (" << album.release_year_ << ", " << album.record_label_ << ") [" << album.tracks_.size() << " tracks]";
    return os;
}

void Album::AddTrack(const AudioTrack& track) {
    tracks_.push_back(track);
}

void Album::RemoveTrack(const std::string& track_title) {
    for (auto it = tracks_.begin(); it != tracks_.end(); it++) {
        if (it->GetMetadata().GetTitle() == track_title) {
            tracks_.erase(it);
            return;
        }
    }
    throw TrackNotFoundException("Track '" + track_title + "' not found in album '" + title_ + "'.");
}

double Album::CalculateTotalDurationSec() const {
    double total = 0.0;
    for (const auto& track : tracks_)
        total += track.GetDurationSec();
    
    return total;
}

const AudioTrack* Album::FindTrack(const std::string& track_title) const {
    for (const auto& track : tracks_) {
        if (track.GetMetadata().GetTitle() == track_title)
            return &track;
    }
    return NULL;
}

const std::string& Album::GetTitle() const {
    return title_;
}

int Album::GetReleaseYear() const {
    return release_year_;
}

const std::string& Album::GetRecordLabel() const {
    return record_label_;
}

const std::vector<AudioTrack>& Album::GetTracks() const {
    return tracks_;
}

size_t Album::GetTracksCount() const {
    return tracks_.size();
}