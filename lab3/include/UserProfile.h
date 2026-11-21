/**
 * @file UserProfile.h
 * @brief Declaration of the UserProfile class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <string>

/**
 * @brief Manages listener account credentials, email, music taste preferences and favorite track tallies.
 */
class UserProfile {
public:
    /**
     * @brief Constructs a UserProfile.
     * @param username User screen name.
     * @param email Account email.
     * @param favorite_genre Preferred musical genre.
     * @param tracks_favorited_count Total number of favorited tracks.
     */
    UserProfile(const std::string& username = "OOOnikproOOO", const std::string& email = "momotnikita693@example.com", const std::string& favorite_genre = "Rock", int tracks_favorited_count = 0);

    /**
     * @brief Compares two UserProfile instances for equality.
     * @param other Profile to compare with.
     * @return true if username and email match.
     */
    bool operator==(const UserProfile& other) const;

    /**
     * @brief Compares two UserProfile instances for inequality.
     * @param other Profile to compare with.
     * @return true if username or email differ.
     */
    bool operator!=(const UserProfile& other) const;

    /**
     * @brief Stream output operator for formatting UserProfile info.
     * @param os Output stream.
     * @param profile Profile instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const UserProfile& profile);

    /**
     * @brief Updates account email address.
     * @param email New email address.
     */
    void SetEmail(const std::string& email);

    /**
     * @brief Updates preferred genre.
     * @param genre Genre name.
     */
    void SetFavoriteGenre(const std::string& genre);

    /**
     * @brief Increments favorited tracks counter.
     */
    void IncrementFavorites();

    /**
     * @brief Decrements favorited tracks counter.
     */
    void DecrementFavorites();

    /**
     * @brief Formats user profile card string.
     * @return Formatted profile summary.
     */
    std::string FormatProfileCard() const;

    /**
     * @brief Gets account username.
     * @return Reference to username string.
     */
    const std::string& GetUsername() const;

    /**
     * @brief Gets account email.
     * @return Reference to email string.
     */
    const std::string& GetEmail() const;

    /**
     * @brief Gets preferred musical genre.
     * @return Reference to favorite genre string.
     */
    const std::string& GetFavoriteGenre() const;

    /**
     * @brief Gets count of favorited tracks.
     * @return Number of favorited tracks.
     */
    int GetTracksFavoritedCount() const;

private:
    std::string username_;
    std::string email_;
    std::string favorite_genre_;
    int tracks_favorited_count_;
};

#endif