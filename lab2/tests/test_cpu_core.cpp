/**
 * @file test_cpu_core.cpp
 * @brief Unit tests for the CPUCore class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "CPUCore.h"
#include "ThermalThrottlingException.h"
#include "OverheatingException.h"

TEST(CPUCoreTest, ConstructorAndGetters) {
    CPUCore core(0, 3600, true);
    EXPECT_EQ(core.GetCoreId(), 0);
    EXPECT_EQ(core.GetBaseClockMhz(), 3600);
    EXPECT_EQ(core.GetCurrentClockMhz(), 3600);
    EXPECT_DOUBLE_EQ(core.GetLoadPercentage(), 0.0);
    EXPECT_DOUBLE_EQ(core.GetTemperatureCelsius(), 35.0);
    EXPECT_TRUE(core.IsHyperthreadingActive());
}

TEST(CPUCoreTest, LoadUpdateAndClockScaling) {
    CPUCore core(1, 3000, false);
    core.UpdateLoad(50.0);
    EXPECT_DOUBLE_EQ(core.GetLoadPercentage(), 50.0);
    EXPECT_EQ(core.GetCurrentClockMhz(), 3000);

    core.UpdateLoad(-10.0);
    EXPECT_DOUBLE_EQ(core.GetLoadPercentage(), 0.0);

    core.UpdateLoad(150.0);
    EXPECT_DOUBLE_EQ(core.GetLoadPercentage(), 100.0);
    EXPECT_EQ(core.GetCurrentClockMhz(), 3600);
}

TEST(CPUCoreTest, CoolDownBehavior) {
    CPUCore core(0, 3200);
    core.CoolDown(10.0);
    EXPECT_DOUBLE_EQ(core.GetTemperatureCelsius(), 35.0);
}

TEST(CPUCoreTest, BoostClockAndThrottle) {
    CPUCore core(0, 3200);
    EXPECT_TRUE(core.BoostClock(4500));
    EXPECT_EQ(core.GetCurrentClockMhz(), 4500);

    EXPECT_FALSE(core.BoostClock(2000));

    core.Throttle(0.5);
    EXPECT_EQ(core.GetCurrentClockMhz(), 2250);
}

TEST(CPUCoreTest, ThermalThrottlingAndOverheatingExceptions) {
    CPUCore core(0, 3200);
    EXPECT_THROW(core.ExecuteInstructions(65000000LL), ThermalThrottlingException);

    CPUCore hot_core(1, 3200);
    EXPECT_THROW(hot_core.ExecuteInstructions(80000000LL), OverheatingException);
}

TEST(CPUCoreTest, EqualityAndStream) {
    CPUCore c1(0, 3200, true);
    CPUCore c2(0, 3200, true);
    CPUCore c3(1, 3200, true);

    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c1 != c3);

    std::stringstream ss;
    ss << c1;
    EXPECT_NE(ss.str().find("Core #0"), std::string::npos);
}