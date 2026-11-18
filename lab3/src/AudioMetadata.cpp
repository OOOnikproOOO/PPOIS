/**
 * @file AudioMetadata.cpp
 * @brief Implementation of AudioMetadata methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "AudioMetadata.h"

AudioMetadata::AudioMetadata(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre, int year, int track_number) : 
    title_(title), artist_(artist), album_(album), genre_(genre), year_(year), track_number_(track_number) {}

bool AudioMetadata::operator==(const AudioMetadata& other) const {
    return title_ == other.title_ && artist_ == other.artist_ &&
           album_ == other.album_ && genre_ == other.genre_ &&
           year_ == other.year_ && track_number_ == other.track_number_;
}

bool AudioMetadata::operator!=(const AudioMetadata& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AudioMetadata& meta) {
    os << meta.artist_ << " - " << meta.title_ << " [" << meta.album_ << ", " << meta.year_ << "]";
    return os;
}

void AudioMetadata::UpdateMetadata(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre, int year, int track_number) {
    title_ = title;
    artist_ = artist;
    album_ = album;
    genre_ = genre;
    year_ = year;
    track_number_ = track_number;
}

std::string AudioMetadata::FormatDisplayString() const {
    return artist_ + " - " + title_ + " (" + std::to_string(year_) + ")";
}

bool AudioMetadata::MatchesQuery(const std::string& query) const {
    if (query.empty())
        return true;
    
    return title_.find(query) != std::string::npos || artist_.find(query) != std::string::npos;
}

bool AudioMetadata::Validate() const {
    const int kMinYear = 1900;
    const int kMaxYear = 2100;
    const int kMinTrackNum = 1;
    const int kMaxTrackNum = 999;
    return !title_.empty() && !artist_.empty() &&
           year_ >= kMinYear && year_ <= kMaxYear &&
           track_number_ >= kMinTrackNum && track_number_ <= kMaxTrackNum;
}

const std::string& AudioMetadata::GetTitle() const {
    return title_;
}

const std::string& AudioMetadata::GetArtist() const {
    return artist_;
}

const std::string& AudioMetadata::GetAlbum() const {
    return album_;
}

const std::string& AudioMetadata::GetGenre() const {
    return genre_;
}

int AudioMetadata::GetYear() const {
    return year_;
}

int AudioMetadata::GetTrackNumber() const {
    return track_number_;
}