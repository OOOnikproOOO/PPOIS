/**
 * @file test_vrm.cpp
 * @brief Unit tests for the VRM class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "VRM.h"
#include "OverheatingException.h"
#include "VoltageInstabilityException.h"

TEST(VRMTest, ConstructorAndGetters) {
    VRM vrm(14, 1.20, 40.0, 93.5);
    EXPECT_EQ(vrm.GetPhaseCount(), 14);
    EXPECT_DOUBLE_EQ(vrm.GetVCoreVoltage(), 1.20);
    EXPECT_DOUBLE_EQ(vrm.GetTemperatureCelsius(), 40.0);
    EXPECT_DOUBLE_EQ(vrm.GetEfficiencyPercentage(), 93.5);
}

TEST(VRMTest, SetVCoreVoltageAndExceptions) {
    VRM vrm;
    vrm.SetVCoreVoltage(1.35);
    EXPECT_DOUBLE_EQ(vrm.GetVCoreVoltage(), 1.35);

    EXPECT_THROW(vrm.SetVCoreVoltage(0.40), VoltageInstabilityException);
    EXPECT_THROW(vrm.SetVCoreVoltage(2.10), VoltageInstabilityException);
}

TEST(VRMTest, SupplyCurrentAndOverheatingException) {
    VRM vrm(16, 1.25, 40.0, 90.0);
    vrm.SupplyCurrent(50.0);
    EXPECT_GT(vrm.GetTemperatureCelsius(), 40.0);

    EXPECT_THROW(vrm.SupplyCurrent(1000.0), OverheatingException);
}

TEST(VRMTest, CoolDownAndPowerLossCalculation) {
    VRM vrm(16, 1.25, 60.0, 90.0);
    vrm.CoolDown(20.0);
    EXPECT_DOUBLE_EQ(vrm.GetTemperatureCelsius(), 40.0);

    vrm.CoolDown(100.0);
    EXPECT_DOUBLE_EQ(vrm.GetTemperatureCelsius(), 25.0);

    double loss = vrm.CalculatePowerLossWatts(100.0);
    EXPECT_NEAR(loss, 12.5, 0.001);
}

TEST(VRMTest, EqualityAndStream) {
    VRM v1(16, 1.25, 42.0, 92.0);
    VRM v2(16, 1.25, 42.0, 92.0);
    VRM v3(12, 1.25, 42.0, 92.0);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_TRUE(v1 != v3);

    std::ostringstream oss;
    oss << v1;
    EXPECT_FALSE(oss.str().empty());
}