/**
 * @file test_pitch_shifter.cpp
 * @brief Unit tests for PitchShifter class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PitchShifter.h"

TEST(PitchShifterTest, ConstructorAndGetters) {
    PitchShifter ps(2, 1.25, "HighQuality", true);
    EXPECT_EQ(ps.GetSemitonesOffset(), 2);
    EXPECT_DOUBLE_EQ(ps.GetTempoMultiplier(), 1.25);
    EXPECT_EQ(ps.GetQualityMode(), "HighQuality");
    EXPECT_TRUE(ps.IsActive());
}

TEST(PitchShifterTest, PitchAndTempoCalculations) {
    PitchShifter ps;
    ps.SetPitchOffset(12);
    EXPECT_NEAR(ps.CalculateFrequencyMultiplier(), 2.0, 0.01);

    ps.SetPitchOffset(-12);
    EXPECT_NEAR(ps.CalculateFrequencyMultiplier(), 0.5, 0.01);

    ps.SetTempo(1.5);
    EXPECT_DOUBLE_EQ(ps.GetTempoMultiplier(), 1.5);
    EXPECT_TRUE(ps.IsActive());

    ps.ResetPitch();
    EXPECT_EQ(ps.GetSemitonesOffset(), 0);
    EXPECT_DOUBLE_EQ(ps.GetTempoMultiplier(), 1.0);
    EXPECT_FALSE(ps.IsActive());
}

TEST(PitchShifterTest, LimitClamping) {
    PitchShifter ps;
    ps.SetPitchOffset(20);
    EXPECT_EQ(ps.GetSemitonesOffset(), 12);

    ps.SetPitchOffset(-30);
    EXPECT_EQ(ps.GetSemitonesOffset(), -12);

    ps.SetTempo(5.0);
    EXPECT_DOUBLE_EQ(ps.GetTempoMultiplier(), 2.0);

    ps.SetTempo(0.1);
    EXPECT_DOUBLE_EQ(ps.GetTempoMultiplier(), 0.5);
}

TEST(PitchShifterTest, EqualityAndStream) {
    PitchShifter p1(3, 1.0);
    PitchShifter p2(3, 1.0);
    PitchShifter p3(0, 1.0);

    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_FALSE(oss.str().empty());
}