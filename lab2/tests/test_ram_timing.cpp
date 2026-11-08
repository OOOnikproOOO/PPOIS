/**
 * @file test_ram_timing.cpp
 * @brief Unit tests for the RAMTiming class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "RAMTiming.h"

TEST(RAMTimingTest, ConstructorAndGetters) {
    RAMTiming timing(16, 18, 18, 36, 1);
    EXPECT_EQ(timing.GetCasLatency(), 16);
    EXPECT_EQ(timing.GetTrcd(), 18);
    EXPECT_EQ(timing.GetTrp(), 18);
    EXPECT_EQ(timing.GetTras(), 36);
    EXPECT_EQ(timing.GetCommandRate(), 1);
}

TEST(RAMTimingTest, TrueLatencyCalculation) {
    RAMTiming timing(16, 18, 18, 36, 1);
    EXPECT_DOUBLE_EQ(timing.CalculateTrueLatencyNs(0), 0.0);
    EXPECT_NEAR(timing.CalculateTrueLatencyNs(3200), 10.0, 0.001);
}

TEST(RAMTimingTest, ValidationLogic) {
    RAMTiming valid_timing(16, 18, 18, 36);
    EXPECT_TRUE(valid_timing.ValidateTimings());

    RAMTiming invalid_tras(16, 18, 18, 20);
    EXPECT_FALSE(invalid_tras.ValidateTimings());

    RAMTiming zero_cl(0, 18, 18, 36);
    EXPECT_FALSE(zero_cl.ValidateTimings());
}

TEST(RAMTimingTest, OptimizationAndComparison) {
    RAMTiming timing;
    timing.OptimizeForFrequency(6000);
    EXPECT_EQ(timing.GetCasLatency(), 36);

    timing.OptimizeForFrequency(2400);
    EXPECT_EQ(timing.GetCasLatency(), 14);

    RAMTiming ddr4_cl16(16, 18, 18, 36);
    RAMTiming ddr5_cl36(36, 36, 36, 76);
    EXPECT_TRUE(ddr4_cl16.IsFasterThan(ddr5_cl36, 3200, 5200));
}

TEST(RAMTimingTest, EqualityAndStream) {
    RAMTiming t1(16, 18, 18, 36, 1);
    RAMTiming t2(16, 18, 18, 36, 1);
    RAMTiming t3(14, 14, 14, 34, 1);

    EXPECT_TRUE(t1 == t2);
    EXPECT_TRUE(t1 != t3);

    std::stringstream ss;
    ss << t1;
    EXPECT_EQ(ss.str(), "16-18-18-36 (1T)");
}