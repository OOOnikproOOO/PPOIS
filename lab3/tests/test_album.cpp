/**
 * @file test_album.cpp
 * @brief Unit tests for Album class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Album.h"
#include "TrackNotFoundException.h"

TEST(AlbumTest, ConstructorAndGetters) {
    Album album("Abbey Road", 1969, "Apple Records");
    EXPECT_EQ(album.GetTitle(), "Abbey Road");
    EXPECT_EQ(album.GetReleaseYear(), 1969);
    EXPECT_EQ(album.GetRecordLabel(), "Apple Records");
    EXPECT_EQ(album.GetTracksCount(), 0);
}

TEST(AlbumTest, AddRemoveFindTracks) {
    Album album("Dark Side of the Moon", 1973, "Harvest");
    AudioTrack t1("time.mp3", 425.0, AudioMetadata("Time", "Pink Floyd", "Dark Side", "Rock", 1973, 4));
    AudioTrack t2("money.mp3", 382.0, AudioMetadata("Money", "Pink Floyd", "Dark Side", "Rock", 1973, 6));

    album.AddTrack(t1);
    album.AddTrack(t2);
    EXPECT_EQ(album.GetTracksCount(), 2);
    EXPECT_DOUBLE_EQ(album.CalculateTotalDurationSec(), 807.0);

    const AudioTrack* found = album.FindTrack("Time");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetMetadata().GetTitle(), "Time");

    EXPECT_EQ(album.FindTrack("Nonexistent"), nullptr);

    EXPECT_NO_THROW(album.RemoveTrack("Time"));
    EXPECT_EQ(album.GetTracksCount(), 1);
    EXPECT_THROW(album.RemoveTrack("Time"), TrackNotFoundException);
}

TEST(AlbumTest, EqualityAndStream) {
    Album a1("Album", 2020, "Label");
    Album a2("Album", 2020, "Label");
    Album a3("Other", 2020, "Label");

    EXPECT_EQ(a1, a2);
    EXPECT_NE(a1, a3);

    std::ostringstream oss;
    oss << a1;
    EXPECT_FALSE(oss.str().empty());
}