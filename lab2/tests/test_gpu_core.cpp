/**
 * @file test_gpu_core.cpp
 * @brief Unit tests for the GPUCore class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "GPUCore.h"
#include "ComputerException.h"

TEST(GPUCoreTest, ConstructorAndGetters) {
    GPUCore core(0, 2400);
    EXPECT_EQ(core.GetCoreId(), 0);
    EXPECT_EQ(core.GetClockMhz(), 2400);
    EXPECT_DOUBLE_EQ(core.GetTemperatureCelsius(), 38.0);
    EXPECT_DOUBLE_EQ(core.GetLoadPercentage(), 0.0);
}

TEST(GPUCoreTest, RenderFramesAndCoolDown) {
    GPUCore core(1, 2100);
    core.RenderFrames(100);
    EXPECT_GT(core.GetLoadPercentage(), 0.0);
    EXPECT_GT(core.GetTemperatureCelsius(), 38.0);

    double temp_before = core.GetTemperatureCelsius();
    core.CoolDown(10.0);
    EXPECT_LT(core.GetTemperatureCelsius(), temp_before);

    core.RenderFrames(0);
    core.CoolDown(0.0);
}

TEST(GPUCoreTest, SetClockMhz) {
    GPUCore core(0, 2000);
    core.SetClockMhz(2500);
    EXPECT_EQ(core.GetClockMhz(), 2500);

    EXPECT_THROW(core.SetClockMhz(400), ComputerException);
    EXPECT_THROW(core.SetClockMhz(5000), ComputerException);
}

TEST(GPUCoreTest, ThermalThrottlingAndOverheatingExceptions) {
    GPUCore core(0, 2500);
    // Rendering many frames increases temperature and load
    EXPECT_THROW(core.RenderFrames(1000), ComputerException);
}

TEST(GPUCoreTest, EqualityAndStream) {
    GPUCore c1(0, 2200);
    GPUCore c2(0, 2200);
    GPUCore c3(1, 2500);

    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c1 != c3);

    std::stringstream ss;
    ss << c1;
    EXPECT_NE(ss.str().find("GPU Core"), std::string::npos);
}