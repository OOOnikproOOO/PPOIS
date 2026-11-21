/**
 * @file test_bass_boost_effect.cpp
 * @brief Unit tests for BassBoostEffect class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "BassBoostEffect.h"

TEST(BassBoostEffectTest, ConstructorAndGetters) {
    BassBoostEffect bass(8.0, 100, true);
    EXPECT_DOUBLE_EQ(bass.GetBoostDb(), 8.0);
    EXPECT_EQ(bass.GetCutoffFrequencyHz(), 100);
    EXPECT_TRUE(bass.IsActive());
}

TEST(BassBoostEffectTest, ApplyBassBoost) {
    BassBoostEffect bass(6.0, 120, true);
    double boosted = bass.ApplyBassBoost(0.4);
    EXPECT_GT(boosted, 0.4);

    bass.ToggleEffect(false);
    EXPECT_DOUBLE_EQ(bass.ApplyBassBoost(0.3), 0.3);
}

TEST(BassBoostEffectTest, ParameterAdjustments) {
    BassBoostEffect bass;
    bass.SetBoost(12.0);
    EXPECT_DOUBLE_EQ(bass.GetBoostDb(), 12.0);

    bass.SetBoost(25.0);
    EXPECT_DOUBLE_EQ(bass.GetBoostDb(), 18.0);

    bass.SetCutoff(80);
    EXPECT_EQ(bass.GetCutoffFrequencyHz(), 80);

    bass.SetCutoff(500);
    EXPECT_EQ(bass.GetCutoffFrequencyHz(), 80);
}

TEST(BassBoostEffectTest, EqualityAndStream) {
    BassBoostEffect b1(6.0, 100);
    BassBoostEffect b2(6.0, 100);
    BassBoostEffect b3(12.0, 100);

    EXPECT_EQ(b1, b2);
    EXPECT_NE(b1, b3);

    std::ostringstream oss;
    oss << b1;
    EXPECT_FALSE(oss.str().empty());
}