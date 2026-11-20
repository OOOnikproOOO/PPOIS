/**
 * @file UserProfile.cpp
 * @brief Implementation of UserProfile methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "UserProfile.h"
#include <sstream>

UserProfile::UserProfile(const std::string& username, const std::string& email, const std::string& favorite_genre, int tracks_favorited_count) :
    username_(username), email_(email), favorite_genre_(favorite_genre), tracks_favorited_count_(tracks_favorited_count < 0 ? 0 : tracks_favorited_count) {}

bool UserProfile::operator==(const UserProfile& other) const {
    return username_ == other.username_ &&
           email_ == other.email_;
}

bool UserProfile::operator!=(const UserProfile& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const UserProfile& profile) {
    os << profile.FormatProfileCard();
    return os;
}

void UserProfile::SetEmail(const std::string& email) {
    email_ = email;
}

void UserProfile::SetFavoriteGenre(const std::string& genre) {
    favorite_genre_ = genre;
}

void UserProfile::IncrementFavorites() {
    tracks_favorited_count_++;
}

void UserProfile::DecrementFavorites() {
    if (tracks_favorited_count_ > 0)
        tracks_favorited_count_--;
}

std::string UserProfile::FormatProfileCard() const {
    std::ostringstream oss;
    oss << "User: " << username_ << " <" << email_ << "> [Fav: " << favorite_genre_ << ", Favorites: " << tracks_favorited_count_ << "]";
    return oss.str();
}

const std::string& UserProfile::GetUsername() const {
    return username_;
}

const std::string& UserProfile::GetEmail() const {
    return email_;
}

const std::string& UserProfile::GetFavoriteGenre() const {
    return favorite_genre_;
}

int UserProfile::GetTracksFavoritedCount() const {
    return tracks_favorited_count_;
}