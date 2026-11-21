/**
 * @file test_playback_position.cpp
 * @brief Unit tests for PlaybackPosition class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PlaybackPosition.h"

TEST(PlaybackPositionTest, ConstructorAndGetters) {
    PlaybackPosition pos(240.0, 60.0, 1.25);
    EXPECT_DOUBLE_EQ(pos.GetTotalSec(), 240.0);
    EXPECT_DOUBLE_EQ(pos.GetCurrentSec(), 60.0);
    EXPECT_DOUBLE_EQ(pos.GetPlaybackSpeed(), 1.25);
    EXPECT_FALSE(pos.IsAtEnd());
}

TEST(PlaybackPositionTest, AdvanceAndSpeed) {
    PlaybackPosition pos(100.0, 0.0, 1.5);
    pos.Advance(10.0);
    EXPECT_DOUBLE_EQ(pos.GetCurrentSec(), 15.0);

    pos.Advance(100.0);
    EXPECT_DOUBLE_EQ(pos.GetCurrentSec(), 100.0);
    EXPECT_TRUE(pos.IsAtEnd());
}

TEST(PlaybackPositionTest, SeekAndProgress) {
    PlaybackPosition pos(200.0, 0.0);
    pos.SeekTo(50.0);
    EXPECT_DOUBLE_EQ(pos.GetCurrentSec(), 50.0);
    EXPECT_DOUBLE_EQ(pos.CalculateProgressPercent(), 25.0);

    pos.SeekTo(-50.0);
    EXPECT_DOUBLE_EQ(pos.GetCurrentSec(), 0.0);

    pos.SeekTo(300.0);
    EXPECT_DOUBLE_EQ(pos.GetCurrentSec(), 200.0);

    EXPECT_EQ(pos.FormatTimeElapsed(), "03:20 / 03:20");

    pos.Reset();
    EXPECT_DOUBLE_EQ(pos.GetCurrentSec(), 0.0);
}

TEST(PlaybackPositionTest, EqualityAndStream) {
    PlaybackPosition p1(120.0, 30.0);
    PlaybackPosition p2(120.0, 30.0);
    PlaybackPosition p3(240.0, 30.0);

    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_FALSE(oss.str().empty());
}