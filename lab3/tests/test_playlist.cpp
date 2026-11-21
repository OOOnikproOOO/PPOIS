/**
 * @file test_playlist.cpp
 * @brief Unit tests for Playlist class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Playlist.h"
#include "PlaylistFullException.h"
#include "TrackNotFoundException.h"

TEST(PlaylistTest, ConstructorAndGetters) {
    Playlist pl("Workout", true, 50);
    EXPECT_EQ(pl.GetName(), "Workout");
    EXPECT_TRUE(pl.IsPublic());
    EXPECT_EQ(pl.GetMaxCapacity(), 50u);
    EXPECT_EQ(pl.GetTracksCount(), 0u);
}

TEST(PlaylistTest, AddRemoveClearTracks) {
    Playlist pl("Roadtrip", false, 2);
    AudioTrack t1("song1.mp3", 180.0);
    AudioTrack t2("song2.mp3", 220.0);
    AudioTrack t3("song3.mp3", 200.0);

    pl.AddTrack(t1);
    pl.AddTrack(t2);
    EXPECT_EQ(pl.GetTracksCount(), 2u);
    EXPECT_DOUBLE_EQ(pl.CalculateTotalDurationSec(), 400.0);

    EXPECT_THROW(pl.AddTrack(t3), PlaylistFullException);

    pl.RemoveTrack(0);
    EXPECT_EQ(pl.GetTracksCount(), 1u);
    EXPECT_THROW(pl.RemoveTrack(5), TrackNotFoundException);

    pl.Clear();
    EXPECT_EQ(pl.GetTracksCount(), 0u);
}

TEST(PlaylistTest, MoveTrack) {
    Playlist pl("Mix", true, 10);
    AudioTrack t1("t1.mp3", 100.0, AudioMetadata("Track 1"));
    AudioTrack t2("t2.mp3", 100.0, AudioMetadata("Track 2"));

    pl.AddTrack(t1);
    pl.AddTrack(t2);
    pl.MoveTrack(0, 1);
    EXPECT_EQ(pl.GetTracks()[0].GetMetadata().GetTitle(), "Track 2");
    EXPECT_EQ(pl.GetTracks()[1].GetMetadata().GetTitle(), "Track 1");

    pl.MoveTrack(0, 0);
    EXPECT_EQ(pl.GetTracks()[0].GetMetadata().GetTitle(), "Track 2");

    EXPECT_THROW(pl.MoveTrack(0, 10), TrackNotFoundException);
}

TEST(PlaylistTest, EqualityAndStream) {
    Playlist p1("List", true, 10);
    Playlist p2("List", true, 10);
    Playlist p3("Other", true, 10);

    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_FALSE(oss.str().empty());
}