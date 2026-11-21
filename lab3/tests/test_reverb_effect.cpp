/**
 * @file test_reverb_effect.cpp
 * @brief Unit tests for ReverbEffect class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "ReverbEffect.h"

TEST(ReverbEffectTest, ConstructorAndGetters) {
    ReverbEffect reverb(0.7, 0.4, 0.3, true);
    EXPECT_DOUBLE_EQ(reverb.GetRoomSize(), 0.7);
    EXPECT_DOUBLE_EQ(reverb.GetDamping(), 0.4);
    EXPECT_DOUBLE_EQ(reverb.GetWetLevel(), 0.3);
    EXPECT_TRUE(reverb.IsActive());
}

TEST(ReverbEffectTest, ProcessSampleActiveAndBypass) {
    ReverbEffect reverb(0.8, 0.2, 0.5, true);
    double out = reverb.ProcessSample(1.0);
    EXPECT_GT(out, 0.0);

    reverb.ToggleEffect(false);
    EXPECT_DOUBLE_EQ(reverb.ProcessSample(0.5), 0.5);
}

TEST(ReverbEffectTest, ParameterClamping) {
    ReverbEffect reverb;
    reverb.SetRoomSize(0.9);
    EXPECT_DOUBLE_EQ(reverb.GetRoomSize(), 0.9);

    reverb.SetRoomSize(1.5);
    EXPECT_DOUBLE_EQ(reverb.GetRoomSize(), 0.9);

    reverb.SetDamping(0.2);
    EXPECT_DOUBLE_EQ(reverb.GetDamping(), 0.2);

    reverb.SetWetLevel(0.4);
    EXPECT_DOUBLE_EQ(reverb.GetWetLevel(), 0.4);
}

TEST(ReverbEffectTest, EqualityAndStream) {
    ReverbEffect r1(0.5, 0.3, 0.2, true);
    ReverbEffect r2(0.5, 0.3, 0.2, true);
    ReverbEffect r3(0.9, 0.3, 0.2, true);

    EXPECT_EQ(r1, r2);
    EXPECT_NE(r1, r3);

    std::ostringstream oss;
    oss << r1;
    EXPECT_FALSE(oss.str().empty());
}