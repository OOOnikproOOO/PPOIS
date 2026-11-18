/**
 * @file MusicLibrary.cpp
 * @brief Implementation of MusicLibrary methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "MusicLibrary.h"
#include "TrackNotFoundException.h"
#include "PlaylistNotFoundException.h"

MusicLibrary::MusicLibrary(const std::string& library_name) : library_name_(library_name), tracks_(), albums_(), artists_(), playlists_() {}

bool MusicLibrary::operator==(const MusicLibrary& other) const {
    return library_name_ == other.library_name_ &&
           tracks_ == other.tracks_ &&
           albums_ == other.albums_ &&
           artists_ == other.artists_ &&
           playlists_ == other.playlists_;
}

bool MusicLibrary::operator!=(const MusicLibrary& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const MusicLibrary& lib) {
    os << "MusicLibrary: " << lib.library_name_ << " [" << lib.tracks_.size() << " tracks, " << lib.albums_.size() << " albums, " << lib.playlists_.size() << " playlists]";
    return os;
}

void MusicLibrary::AddTrack(const AudioTrack& track) {
    tracks_.push_back(track);
}

const AudioTrack& MusicLibrary::FindTrackByTitle(const std::string& title) const {
    for (const auto& track : tracks_) {
        if (track.GetMetadata().GetTitle() == title)
            return track;
    }
    throw TrackNotFoundException("Track '" + title + "' was not found in library '" + library_name_ + "'.");
}

void MusicLibrary::AddPlaylist(const Playlist& playlist) {
    playlists_.push_back(playlist);
}

const Playlist& MusicLibrary::FindPlaylistByName(const std::string& name) const {
    for (const auto& playlist : playlists_) {
        if (playlist.GetName() == name)
            return playlist;
    }
    throw PlaylistNotFoundException("Playlist '" + name + "' was not found in library '" + library_name_ + "'.");
}

double MusicLibrary::GetTotalListeningTimeSec() const {
    double total = 0.0;
    for (const auto& track : tracks_)
        total += track.GetDurationSec() * track.GetPlayCount();
    return total;
}

const std::string& MusicLibrary::GetLibraryName() const {
    return library_name_;
}

const std::vector<AudioTrack>& MusicLibrary::GetTracks() const {
    return tracks_;
}

const std::vector<Album>& MusicLibrary::GetAlbums() const {
    return albums_;
}

const std::vector<Artist>& MusicLibrary::GetArtists() const {
    return artists_;
}

const std::vector<Playlist>& MusicLibrary::GetPlaylists() const {
    return playlists_;
}