/**
 * @file test_cooling_system.cpp
 * @brief Unit tests for the CoolingSystem class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "CoolingSystem.h"
#include "Exceptions.h"

TEST(CoolingSystemTest, ConstructorAndGetters) {
    CoolingSystem cooling("Standard", 65.0);
    EXPECT_EQ(cooling.GetFanProfile(), "Standard");
    EXPECT_DOUBLE_EQ(cooling.GetTargetTemperatureCelsius(), 65.0);
    EXPECT_EQ(cooling.GetFanCount(), 0);
    EXPECT_EQ(cooling.GetLiquidCooler().GetRadiatorSizeMm(), 360);
}

TEST(CoolingSystemTest, AddFanAndAccess) {
    CoolingSystem cooling;
    cooling.AddFan(CoolingFan("Intake Fan #1", 120, 1000, 2000, 50));
    cooling.AddFan(CoolingFan("Exhaust Fan #1", 120, 1000, 2000, 50));

    EXPECT_EQ(cooling.GetFanCount(), 2);
    EXPECT_EQ(cooling.GetFan(0).GetFanName(), "Intake Fan #1");
    EXPECT_EQ(cooling.GetFan(1).GetFanName(), "Exhaust Fan #1");

    EXPECT_THROW(cooling.GetFan(-1), DeviceNotFoundException);
    EXPECT_THROW(cooling.GetFan(2), DeviceNotFoundException);
}

TEST(CoolingSystemTest, ApplyProfile) {
    CoolingSystem cooling;
    cooling.AddFan(CoolingFan("Fan 1", 120, 1000, 2000, 50));

    cooling.ApplyProfile("Performance");
    EXPECT_EQ(cooling.GetFanProfile(), "Performance");
    EXPECT_EQ(cooling.GetFan(0).GetPwmDutyCycle(), 75);

    cooling.ApplyProfile("Silent");
    EXPECT_EQ(cooling.GetFan(0).GetPwmDutyCycle(), 30);

    cooling.ApplyProfile("Full Speed");
    EXPECT_EQ(cooling.GetFan(0).GetPwmDutyCycle(), 100);

    EXPECT_THROW(cooling.ApplyProfile("NonExistentProfile"), ComputerException);
}

TEST(CoolingSystemTest, CalculateAirflowCfm) {
    CoolingSystem cooling("Performance", 60.0);
    cooling.AddFan(CoolingFan("Fan 1", 120, 2000, 2000, 100));
    cooling.AddFan(CoolingFan("Fan 2", 120, 2000, 2000, 100));

    EXPECT_GT(cooling.CalculateTotalAirflowCfm(), 100.0);
}

TEST(CoolingSystemTest, EqualityAndStream) {
    CoolingSystem c1("Standard", 65.0);
    CoolingSystem c2("Standard", 65.0);
    CoolingSystem c3("Silent", 70.0);

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_TRUE(c1 != c3);

    std::ostringstream oss;
    oss << c1;
    EXPECT_FALSE(oss.str().empty());
}