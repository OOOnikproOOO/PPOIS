/**
 * @file test_liquid_cooler.cpp
 * @brief Unit tests for the LiquidCooler class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "LiquidCooler.h"
#include "ComputerException.h"
#include "OverheatingException.h"

TEST(LiquidCoolerTest, ConstructorAndGetters) {
    LiquidCooler cooler("NZXT Kraken X73", 360, 2800, 28.0, 160.0);
    EXPECT_EQ(cooler.GetModelName(), "NZXT Kraken X73");
    EXPECT_EQ(cooler.GetRadiatorSizeMm(), 360);
    EXPECT_EQ(cooler.GetPumpRpm(), 2800);
    EXPECT_DOUBLE_EQ(cooler.GetCoolantTemperatureCelsius(), 28.0);
    EXPECT_DOUBLE_EQ(cooler.GetFlowRateLph(), 160.0);
}

TEST(LiquidCoolerTest, SetPumpSpeedAndExceptions) {
    LiquidCooler cooler;
    cooler.SetPumpSpeed(2000);
    EXPECT_EQ(cooler.GetPumpRpm(), 2000);
    EXPECT_LT(cooler.GetFlowRateLph(), 150.0);

    EXPECT_THROW(cooler.SetPumpSpeed(600), ComputerException);
}

TEST(LiquidCoolerTest, AbsorbAndDissipateHeat) {
    LiquidCooler cooler("Arctic Liquid Freezer II 360", 360, 2800, 30.0, 150.0);
    cooler.AbsorbHeat(100.0);
    EXPECT_GT(cooler.GetCoolantTemperatureCelsius(), 30.0);

    cooler.DissipateHeat(10.0);
    EXPECT_LT(cooler.GetCoolantTemperatureCelsius(), 35.0);

    cooler.DissipateHeat(100.0);
    EXPECT_DOUBLE_EQ(cooler.GetCoolantTemperatureCelsius(), 22.0);

    EXPECT_THROW(cooler.AbsorbHeat(2000.0), OverheatingException);
}

TEST(LiquidCoolerTest, EqualityAndStream) {
    LiquidCooler c1("Arctic Liquid Freezer II 360", 360, 2800, 30.0, 150.0);
    LiquidCooler c2("Arctic Liquid Freezer II 360", 360, 2800, 30.0, 150.0);
    LiquidCooler c3("Corsair H150i", 360, 2800, 30.0, 150.0);

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_TRUE(c1 != c3);

    std::ostringstream oss;
    oss << c1;
    EXPECT_FALSE(oss.str().empty());
}