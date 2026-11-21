/**
 * @file test_power_rail.cpp
 * @brief Unit tests for the PowerRail class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PowerRail.h"
#include "PowerSupplyOverloadException.h"

TEST(PowerRailTest, ConstructorAndGetters) {
    PowerRail rail("+12V", 12.0, 5.0, 70.0);
    EXPECT_EQ(rail.GetRailName(), "+12V");
    EXPECT_DOUBLE_EQ(rail.GetNominalVoltage(), 12.0);
    EXPECT_DOUBLE_EQ(rail.GetCurrentAmperes(), 5.0);
    EXPECT_DOUBLE_EQ(rail.GetMaxAmperes(), 70.0);
}

TEST(PowerRailTest, DrawAndReleaseCurrent) {
    PowerRail rail("+12V", 12.0, 0.0, 50.0);
    rail.DrawCurrent(25.0);
    EXPECT_DOUBLE_EQ(rail.GetCurrentAmperes(), 25.0);
    EXPECT_DOUBLE_EQ(rail.CalculateCurrentPowerWatts(), 300.0);

    rail.ReleaseCurrent(10.0);
    EXPECT_DOUBLE_EQ(rail.GetCurrentAmperes(), 15.0);

    rail.ReleaseCurrent(50.0);
    EXPECT_DOUBLE_EQ(rail.GetCurrentAmperes(), 0.0);

    EXPECT_THROW(rail.DrawCurrent(55.0), PowerSupplyOverloadException);
}

TEST(PowerRailTest, EqualityAndStream) {
    PowerRail r1("+5V", 5.0, 2.0, 25.0);
    PowerRail r2("+5V", 5.0, 2.0, 25.0);
    PowerRail r3("+3.3V", 3.3, 2.0, 25.0);

    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
    EXPECT_TRUE(r1 != r3);

    std::ostringstream oss;
    oss << r1;
    EXPECT_FALSE(oss.str().empty());
}