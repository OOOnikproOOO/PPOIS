/**
 * @file SmartPlaylist.cpp
 * @brief Implementation of SmartPlaylist methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "SmartPlaylist.h"

SmartPlaylist::SmartPlaylist(const std::string& playlist_name, const std::string& genre_filter, int min_year, bool favorites_only) :
    genre_filter_(genre_filter), min_year_(min_year), favorites_only_(favorites_only), playlist_(playlist_name) {}

bool SmartPlaylist::operator==(const SmartPlaylist& other) const {
    return genre_filter_ == other.genre_filter_ &&
           min_year_ == other.min_year_ &&
           favorites_only_ == other.favorites_only_ &&
           playlist_ == other.playlist_;
}

bool SmartPlaylist::operator!=(const SmartPlaylist& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SmartPlaylist& sp) {
    os << "SmartPlaylist: " << sp.playlist_.GetName() << " [Genre: " << sp.genre_filter_ << ", MinYear: " << sp.min_year_ << ", FavOnly: " << (sp.favorites_only_ ? "Yes" : "No") << "]";
    return os;
}

bool SmartPlaylist::MatchesCriteria(const AudioTrack& track) const {
    const AudioMetadata& meta = track.GetMetadata();
    if (!genre_filter_.empty() && meta.GetGenre() != genre_filter_)
        return false;
    
    if (meta.GetYear() < min_year_)
        return false;
    
    if (favorites_only_ && !track.IsFavorite())
        return false;
    
    return true;
}

size_t SmartPlaylist::ApplyFilter(const std::vector<AudioTrack>& library_tracks) {
    playlist_.Clear();
    size_t added = 0;
    for (const auto& track : library_tracks) {
        if (MatchesCriteria(track)) {
            playlist_.AddTrack(track);
            added++;
        }
    }
    return added;
}

void SmartPlaylist::SetGenreFilter(const std::string& genre) {
    genre_filter_ = genre;
}

void SmartPlaylist::SetMinYear(int year) {
    min_year_ = year;
}

void SmartPlaylist::SetFavoritesOnly(bool enable) {
    favorites_only_ = enable;
}

const std::string& SmartPlaylist::GetGenreFilter() const {
    return genre_filter_;
}

int SmartPlaylist::GetMinYear() const {
    return min_year_;
}

bool SmartPlaylist::IsFavoritesOnly() const {
    return favorites_only_;
}

const Playlist& SmartPlaylist::GetPlaylist() const {
    return playlist_;
}