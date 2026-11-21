/**
 * @file test_smart_playlist.cpp
 * @brief Unit tests for SmartPlaylist class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "SmartPlaylist.h"

TEST(SmartPlaylistTest, ConstructorAndGetters) {
    SmartPlaylist sp("Rock Favorites", "Rock", 1990, true);
    EXPECT_EQ(sp.GetGenreFilter(), "Rock");
    EXPECT_EQ(sp.GetMinYear(), 1990);
    EXPECT_TRUE(sp.IsFavoritesOnly());
    EXPECT_EQ(sp.GetPlaylist().GetName(), "Rock Favorites");
}

TEST(SmartPlaylistTest, FilterCriteriaAndApply) {
    SmartPlaylist sp("Rock Post-2000", "Rock", 2000, false);

    AudioTrack t1("t1.mp3", 200.0, AudioMetadata("Classic Rock", "Artist", "Album", "Rock", 1985));
    AudioTrack t2("t2.mp3", 200.0, AudioMetadata("Modern Rock", "Artist", "Album", "Rock", 2010));
    AudioTrack t3("t3.mp3", 200.0, AudioMetadata("Modern Pop", "Artist", "Album", "Pop", 2015));

    EXPECT_FALSE(sp.MatchesCriteria(t1));
    EXPECT_TRUE(sp.MatchesCriteria(t2));
    EXPECT_FALSE(sp.MatchesCriteria(t3));

    std::vector<AudioTrack> library = {t1, t2, t3};
    size_t added = sp.ApplyFilter(library);
    EXPECT_EQ(added, 1u);
    EXPECT_EQ(sp.GetPlaylist().GetTracksCount(), 1u);
}

TEST(SmartPlaylistTest, FavoritesFilter) {
    SmartPlaylist sp("Favs", "", 1900, true);
    AudioTrack t1("t1.mp3", 100.0);
    AudioTrack t2("t2.mp3", 100.0);
    t2.ToggleFavorite();

    EXPECT_FALSE(sp.MatchesCriteria(t1));
    EXPECT_TRUE(sp.MatchesCriteria(t2));

    sp.SetGenreFilter("Jazz");
    sp.SetMinYear(2020);
    sp.SetFavoritesOnly(false);
    EXPECT_EQ(sp.GetGenreFilter(), "Jazz");
    EXPECT_EQ(sp.GetMinYear(), 2020);
    EXPECT_FALSE(sp.IsFavoritesOnly());
}

TEST(SmartPlaylistTest, EqualityAndStream) {
    SmartPlaylist s1("List", "Rock", 2000, false);
    SmartPlaylist s2("List", "Rock", 2000, false);
    SmartPlaylist s3("List", "Pop", 2000, false);

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}