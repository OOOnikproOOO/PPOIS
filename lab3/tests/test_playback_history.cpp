/**
 * @file test_playback_history.cpp
 * @brief Unit tests for PlaybackHistory class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PlaybackHistory.h"

TEST(PlaybackHistoryTest, ConstructorAndGetters) {
    PlaybackHistory history(50);
    EXPECT_EQ(history.GetMaxEntries(), 50u);
    EXPECT_EQ(history.GetEntriesCount(), 0u);
    EXPECT_EQ(history.GetTotalPlayedCount(), 0);
}

TEST(PlaybackHistoryTest, RecordAndRecentTracks) {
    PlaybackHistory history(3);
    history.RecordTrack("Song A");
    history.RecordTrack("Song B");
    history.RecordTrack("Song C");
    EXPECT_EQ(history.GetEntriesCount(), 3u);
    EXPECT_EQ(history.GetTotalPlayedCount(), 3);

    auto recent = history.GetRecentTracks(2);
    ASSERT_EQ(recent.size(), 2u);
    EXPECT_EQ(recent[0], "Song C");
    EXPECT_EQ(recent[1], "Song B");

    history.RecordTrack("Song D");
    EXPECT_EQ(history.GetEntriesCount(), 3u);
    EXPECT_FALSE(history.ContainsRecord("Song A"));
    EXPECT_TRUE(history.ContainsRecord("Song D"));
}

TEST(PlaybackHistoryTest, ClearHistory) {
    PlaybackHistory history;
    history.RecordTrack("Song 1");
    history.ClearHistory();
    EXPECT_EQ(history.GetEntriesCount(), 0u);
    EXPECT_FALSE(history.ContainsRecord("Song 1"));
}

TEST(PlaybackHistoryTest, EqualityAndStream) {
    PlaybackHistory h1(10);
    PlaybackHistory h2(10);
    PlaybackHistory h3(20);

    EXPECT_EQ(h1, h2);
    EXPECT_NE(h1, h3);

    std::ostringstream oss;
    oss << h1;
    EXPECT_FALSE(oss.str().empty());
}