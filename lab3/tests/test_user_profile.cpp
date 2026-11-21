/**
 * @file test_user_profile.cpp
 * @brief Unit tests for UserProfile class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "UserProfile.h"

TEST(UserProfileTest, ConstructorAndGetters) {
    UserProfile user("Alex", "alex@mail.com", "Electronic", 15);
    EXPECT_EQ(user.GetUsername(), "Alex");
    EXPECT_EQ(user.GetEmail(), "alex@mail.com");
    EXPECT_EQ(user.GetFavoriteGenre(), "Electronic");
    EXPECT_EQ(user.GetTracksFavoritedCount(), 15);
}

TEST(UserProfileTest, MutatorsAndTally) {
    UserProfile user;
    user.SetEmail("new@mail.com");
    EXPECT_EQ(user.GetEmail(), "new@mail.com");

    user.SetFavoriteGenre("Classical");
    EXPECT_EQ(user.GetFavoriteGenre(), "Classical");

    user.IncrementFavorites();
    EXPECT_EQ(user.GetTracksFavoritedCount(), 1);

    user.DecrementFavorites();
    EXPECT_EQ(user.GetTracksFavoritedCount(), 0);

    user.DecrementFavorites();
    EXPECT_EQ(user.GetTracksFavoritedCount(), 0);
}

TEST(UserProfileTest, FormattingCard) {
    UserProfile user("John", "john@music.com", "Jazz", 5);
    std::string card = user.FormatProfileCard();
    EXPECT_NE(card.find("John"), std::string::npos);
    EXPECT_NE(card.find("john@music.com"), std::string::npos);
    EXPECT_NE(card.find("Jazz"), std::string::npos);
}

TEST(UserProfileTest, EqualityAndStream) {
    UserProfile u1("Same", "same@mail.com");
    UserProfile u2("Same", "same@mail.com");
    UserProfile u3("Other", "other@mail.com");

    EXPECT_EQ(u1, u2);
    EXPECT_NE(u1, u3);

    std::ostringstream oss;
    oss << u1;
    EXPECT_FALSE(oss.str().empty());
}