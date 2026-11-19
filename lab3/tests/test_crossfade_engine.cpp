/**
 * @file test_crossfade_engine.cpp
 * @brief Unit tests for CrossfadeEngine class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "CrossfadeEngine.h"

TEST(CrossfadeEngineTest, ConstructorAndGetters) {
    CrossfadeEngine engine(5.0, true, "Linear");
    EXPECT_DOUBLE_EQ(engine.GetDurationSec(), 5.0);
    EXPECT_TRUE(engine.IsEnabled());
    EXPECT_EQ(engine.GetTransitionCurve(), "Linear");
}

TEST(CrossfadeEngineTest, LinearMixCoefficients) {
    CrossfadeEngine engine(4.0, true, "Linear");
    double v1 = 0.0;
    double v2 = 0.0;

    engine.CalculateMixCoefficients(0.0, v1, v2);
    EXPECT_DOUBLE_EQ(v1, 1.0);
    EXPECT_DOUBLE_EQ(v2, 0.0);

    engine.CalculateMixCoefficients(2.0, v1, v2);
    EXPECT_DOUBLE_EQ(v1, 0.5);
    EXPECT_DOUBLE_EQ(v2, 0.5);

    engine.CalculateMixCoefficients(4.0, v1, v2);
    EXPECT_DOUBLE_EQ(v1, 0.0);
    EXPECT_DOUBLE_EQ(v2, 1.0);
}

TEST(CrossfadeEngineTest, EqualPowerCurve) {
    CrossfadeEngine engine(4.0, true, "EqualPower");
    double v1 = 0.0;
    double v2 = 0.0;

    engine.CalculateMixCoefficients(2.0, v1, v2);
    EXPECT_NEAR(v1 * v1 + v2 * v2, 1.0, 0.01);
}

TEST(CrossfadeEngineTest, ToggleAndSettings) {
    CrossfadeEngine engine;
    engine.SetDuration(8.0);
    EXPECT_DOUBLE_EQ(engine.GetDurationSec(), 8.0);

    engine.ToggleCrossfade(false);
    EXPECT_FALSE(engine.IsEnabled());

    double v1 = 0.0;
    double v2 = 0.0;
    engine.CalculateMixCoefficients(4.0, v1, v2);
    EXPECT_DOUBLE_EQ(v1, 0.0);
    EXPECT_DOUBLE_EQ(v2, 1.0);
}

TEST(CrossfadeEngineTest, EqualityAndStream) {
    CrossfadeEngine c1(4.0);
    CrossfadeEngine c2(4.0);
    CrossfadeEngine c3(8.0);

    EXPECT_EQ(c1, c2);
    EXPECT_NE(c1, c3);

    std::ostringstream oss;
    oss << c1;
    EXPECT_FALSE(oss.str().empty());
}