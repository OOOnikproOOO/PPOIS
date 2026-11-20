/**
 * @file test_playback_statistics.cpp
 * @brief Unit tests for PlaybackStatistics class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PlaybackStatistics.h"

TEST(PlaybackStatisticsTest, ConstructorAndGetters) {
    PlaybackStatistics stats(3600.0, 10, 2, "Rock");
    EXPECT_DOUBLE_EQ(stats.GetTotalListenTimeSec(), 3600.0);
    EXPECT_EQ(stats.GetSessionsCount(), 10);
    EXPECT_EQ(stats.GetSkipsCount(), 2);
    EXPECT_EQ(stats.GetFavoriteGenre(), "Rock");
}

TEST(PlaybackStatisticsTest, RecordSessionAndRates) {
    PlaybackStatistics stats;
    EXPECT_DOUBLE_EQ(stats.GetAverageSessionMinutes(), 0.0);
    EXPECT_DOUBLE_EQ(stats.CalculateSkipRatePercentage(), 0.0);

    stats.RecordSession(180.0, "Rock", false);
    stats.RecordSession(120.0, "Pop", true);

    EXPECT_DOUBLE_EQ(stats.GetTotalListenTimeSec(), 300.0);
    EXPECT_EQ(stats.GetSessionsCount(), 2);
    EXPECT_EQ(stats.GetSkipsCount(), 1);
    EXPECT_EQ(stats.GetFavoriteGenre(), "Pop");
    EXPECT_DOUBLE_EQ(stats.GetAverageSessionMinutes(), 2.5);
    EXPECT_DOUBLE_EQ(stats.CalculateSkipRatePercentage(), 50.0);

    stats.Reset();
    EXPECT_DOUBLE_EQ(stats.GetTotalListenTimeSec(), 0.0);
    EXPECT_EQ(stats.GetSessionsCount(), 0);
    EXPECT_EQ(stats.GetFavoriteGenre(), "Unknown");
}

TEST(PlaybackStatisticsTest, EqualityAndStream) {
    PlaybackStatistics s1(600.0, 2, 0, "Jazz");
    PlaybackStatistics s2(600.0, 2, 0, "Jazz");
    PlaybackStatistics s3(600.0, 3, 0, "Jazz");

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}