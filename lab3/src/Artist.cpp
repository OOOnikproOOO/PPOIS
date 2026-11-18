/**
 * @file Artist.cpp
 * @brief Implementation of Artist methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Artist.h"

Artist::Artist(const std::string& name, const std::string& country, int monthly_listeners) : 
    name_(name), country_(country), monthly_listeners_(monthly_listeners >= 0 ? monthly_listeners : 0), albums_() {}

bool Artist::operator==(const Artist& other) const {
    return name_ == other.name_ &&
           country_ == other.country_ &&
           monthly_listeners_ == other.monthly_listeners_ &&
           albums_ == other.albums_;
}

bool Artist::operator!=(const Artist& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Artist& artist) {
    os << "Artist: " << artist.name_ << " (" << artist.country_ << ", " << artist.monthly_listeners_ << " listeners, " << artist.albums_.size() << " albums)";
    return os;
}

void Artist::AddAlbum(const Album& album) {
    albums_.push_back(album);
}

size_t Artist::CalculateTotalTracksCount() const {
    size_t count = 0;
    for (const auto& album : albums_)
        count += album.GetTracksCount();
    
    return count;
}

const Album* Artist::FindAlbum(const std::string& album_title) const {
    for (const auto& album : albums_) {
        if (album.GetTitle() == album_title)
            return &album;
    }
    return NULL;
}

void Artist::UpdateMonthlyListeners(int delta) {
    monthly_listeners_ += delta;
    if (monthly_listeners_ < 0)
        monthly_listeners_ = 0;
}

const std::string& Artist::GetName() const {
    return name_;
}

const std::string& Artist::GetCountry() const {
    return country_;
}

int Artist::GetMonthlyListeners() const {
    return monthly_listeners_;
}

const std::vector<Album>& Artist::GetAlbums() const {
    return albums_;
}