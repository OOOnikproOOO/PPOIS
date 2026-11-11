/**
 * @file test_cooling_fan.cpp
 * @brief Unit tests for the CoolingFan class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "CoolingFan.h"

TEST(CoolingFanTest, ConstructorAndGetters) {
    CoolingFan fan("be quiet! Silent Wings 4", 140, 1200, 2400, 50);
    EXPECT_EQ(fan.GetFanName(), "be quiet! Silent Wings 4");
    EXPECT_EQ(fan.GetDiameterMm(), 140);
    EXPECT_EQ(fan.GetRpm(), 1200);
    EXPECT_EQ(fan.GetMaxRpm(), 2400);
    EXPECT_EQ(fan.GetPwmDutyCycle(), 50);
}

TEST(CoolingFanTest, SetPwmDutyCycle) {
    CoolingFan fan("Noctua NF-A12x25", 120, 1000, 2000, 50);
    fan.SetPwmDutyCycle(100);
    EXPECT_EQ(fan.GetPwmDutyCycle(), 100);
    EXPECT_EQ(fan.GetRpm(), 2000);

    fan.SetPwmDutyCycle(0);
    EXPECT_EQ(fan.GetPwmDutyCycle(), 0);
    EXPECT_EQ(fan.GetRpm(), 0);

    fan.SetPwmDutyCycle(150);
    EXPECT_EQ(fan.GetPwmDutyCycle(), 100);

    fan.SetPwmDutyCycle(-20);
    EXPECT_EQ(fan.GetPwmDutyCycle(), 0);
}

TEST(CoolingFanTest, CalculateAirflowAndNoise) {
    CoolingFan fan("Noctua NF-A12x25", 120, 2000, 2000, 100);
    EXPECT_NEAR(fan.CalculateAirflowCfm(), 60.0, 0.1);
    EXPECT_NEAR(fan.CalculateNoiseLevelDba(), 35.0, 0.1);

    fan.SetPwmDutyCycle(0);
    EXPECT_DOUBLE_EQ(fan.CalculateAirflowCfm(), 0.0);
    EXPECT_DOUBLE_EQ(fan.CalculateNoiseLevelDba(), 0.0);
}

TEST(CoolingFanTest, EqualityAndStream) {
    CoolingFan f1("Noctua NF-A12x25", 120, 1000, 2000, 50);
    CoolingFan f2("Noctua NF-A12x25", 120, 1000, 2000, 50);
    CoolingFan f3("Noctua NF-A14", 140, 1000, 2000, 50);

    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
    EXPECT_TRUE(f1 != f3);

    std::ostringstream oss;
    oss << f1;
    EXPECT_FALSE(oss.str().empty());
}