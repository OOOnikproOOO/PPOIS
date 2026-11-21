/**
 * @file test_artist.cpp
 * @brief Unit tests for Artist class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Artist.h"

TEST(ArtistTest, ConstructorAndGetters) {
    Artist artist("Hans Zimmer", "Germany", 25000000);
    EXPECT_EQ(artist.GetName(), "Hans Zimmer");
    EXPECT_EQ(artist.GetCountry(), "Germany");
    EXPECT_EQ(artist.GetMonthlyListeners(), 25000000);
    EXPECT_EQ(artist.GetAlbums().size(), 0u);
}

TEST(ArtistTest, AddAlbumAndTrackCount) {
    Artist artist("Queen", "UK", 45000000);
    Album a1("A Night at the Opera", 1975, "EMI");
    a1.AddTrack(AudioTrack("track1.mp3", 200.0));
    a1.AddTrack(AudioTrack("track2.mp3", 240.0));

    Album a2("News of the World", 1977, "EMI");
    a2.AddTrack(AudioTrack("track3.mp3", 180.0));

    artist.AddAlbum(a1);
    artist.AddAlbum(a2);
    EXPECT_EQ(artist.GetAlbums().size(), 2u);
    EXPECT_EQ(artist.CalculateTotalTracksCount(), 3u);

    const Album* found = artist.FindAlbum("News of the World");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetTitle(), "News of the World");
    EXPECT_EQ(artist.FindAlbum("Nonexistent"), nullptr);
}

TEST(ArtistTest, UpdateListeners) {
    Artist artist("Indie Band", "USA", 500);
    artist.UpdateMonthlyListeners(200);
    EXPECT_EQ(artist.GetMonthlyListeners(), 700);

    artist.UpdateMonthlyListeners(-1000);
    EXPECT_EQ(artist.GetMonthlyListeners(), 0);
}

TEST(ArtistTest, EqualityAndStream) {
    Artist art1("Artist", "Country", 100);
    Artist art2("Artist", "Country", 100);
    Artist art3("Other", "Country", 100);

    EXPECT_EQ(art1, art2);
    EXPECT_NE(art1, art3);

    std::ostringstream oss;
    oss << art1;
    EXPECT_FALSE(oss.str().empty());
}