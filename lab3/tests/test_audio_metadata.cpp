/**
 * @file test_audio_metadata.cpp
 * @brief Unit tests for AudioMetadata class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioMetadata.h"

TEST(AudioMetadataTest, ConstructorAndGetters) {
    AudioMetadata meta("Bohemian Rhapsody", "Queen", "A Night at the Opera", "Rock", 1975, 4);
    EXPECT_EQ(meta.GetTitle(), "Bohemian Rhapsody");
    EXPECT_EQ(meta.GetArtist(), "Queen");
    EXPECT_EQ(meta.GetAlbum(), "A Night at the Opera");
    EXPECT_EQ(meta.GetGenre(), "Rock");
    EXPECT_EQ(meta.GetYear(), 1975);
    EXPECT_EQ(meta.GetTrackNumber(), 4);
}

TEST(AudioMetadataTest, UpdateMetadataAndValidation) {
    AudioMetadata meta;
    EXPECT_TRUE(meta.Validate());

    meta.UpdateMetadata("Song", "Artist", "Album", "Pop", 2024, 1);
    EXPECT_EQ(meta.GetTitle(), "Song");
    EXPECT_TRUE(meta.Validate());

    meta.UpdateMetadata("", "Artist", "Album", "Pop", 1800, 0);
    EXPECT_FALSE(meta.Validate());
}

TEST(AudioMetadataTest, FormatDisplayAndSearch) {
    AudioMetadata meta("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", "Hard Rock", 1971, 4);
    EXPECT_EQ(meta.FormatDisplayString(), "Led Zeppelin - Stairway to Heaven (1971)");

    EXPECT_TRUE(meta.MatchesQuery("Stairway"));
    EXPECT_TRUE(meta.MatchesQuery("Zeppelin"));
    EXPECT_FALSE(meta.MatchesQuery("Pink Floyd"));
    EXPECT_TRUE(meta.MatchesQuery(""));
}

TEST(AudioMetadataTest, EqualityAndStream) {
    AudioMetadata m1("Track", "Artist", "Album", "Rock", 2020, 1);
    AudioMetadata m2("Track", "Artist", "Album", "Rock", 2020, 1);
    AudioMetadata m3("Other", "Artist", "Album", "Rock", 2020, 1);

    EXPECT_EQ(m1, m2);
    EXPECT_NE(m1, m3);

    std::ostringstream oss;
    oss << m1;
    EXPECT_FALSE(oss.str().empty());
}