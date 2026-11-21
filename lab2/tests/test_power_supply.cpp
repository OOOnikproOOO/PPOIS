/**
 * @file test_power_supply.cpp
 * @brief Unit tests for the PowerSupply class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PowerSupply.h"
#include "DeviceNotFoundException.h"
#include "PowerSupplyOverloadException.h"

TEST(PowerSupplyTest, ConstructorAndGetters) {
    PowerSupply psu("Seasonic Focus GX-750", 750, "80 PLUS Gold", false);
    EXPECT_EQ(psu.GetModelName(), "Seasonic Focus GX-750");
    EXPECT_EQ(psu.GetRatedWattage(), 750);
    EXPECT_EQ(psu.GetEfficiencyRating(), "80 PLUS Gold");
    EXPECT_FALSE(psu.IsPoweredOn());
    EXPECT_EQ(psu.GetRailCount(), 0);
}

TEST(PowerSupplyTest, AddRailAndAccess) {
    PowerSupply psu;
    psu.AddRail(PowerRail("+12V", 12.0, 10.0, 70.0));
    psu.AddRail(PowerRail("+5V", 5.0, 5.0, 25.0));

    EXPECT_EQ(psu.GetRailCount(), 2);
    EXPECT_EQ(psu.GetRail(0).GetRailName(), "+12V");
    EXPECT_EQ(psu.GetRail(1).GetRailName(), "+5V");

    EXPECT_THROW(psu.GetRail(-1), DeviceNotFoundException);
    EXPECT_THROW(psu.GetRail(2), DeviceNotFoundException);
}

TEST(PowerSupplyTest, PowerOnOff) {
    PowerSupply psu;
    EXPECT_FALSE(psu.IsPoweredOn());
    psu.PowerOn();
    EXPECT_TRUE(psu.IsPoweredOn());
    psu.PowerOff();
    EXPECT_FALSE(psu.IsPoweredOn());
}

TEST(PowerSupplyTest, CalculateTotalPowerDrawWattsAndOverload) {
    PowerSupply psu("Corsair RM850x", 850, "80 PLUS Gold", true);
    psu.AddRail(PowerRail("+12V", 12.0, 30.0, 70.0));
    psu.AddRail(PowerRail("+5V", 5.0, 10.0, 25.0));

    EXPECT_EQ(psu.CalculateTotalPowerDrawWatts(), 410);

    PowerSupply weakPsu("Budget PSU", 200, "80 PLUS Bronze", true);
    weakPsu.AddRail(PowerRail("+12V", 12.0, 20.0, 30.0));
    EXPECT_THROW(weakPsu.CalculateTotalPowerDrawWatts(), PowerSupplyOverloadException);
}

TEST(PowerSupplyTest, CalculateEfficiencyAtLoad) {
    PowerSupply psu("Corsair RM850x", 850, "80 PLUS Gold", true);
    EXPECT_NEAR(psu.CalculateEfficiencyAtLoad(425), 0.90, 0.01);
    EXPECT_NEAR(psu.CalculateEfficiencyAtLoad(100), 0.87, 0.01);
    EXPECT_DOUBLE_EQ(psu.CalculateEfficiencyAtLoad(0), 0.0);
}

TEST(PowerSupplyTest, EqualityAndStream) {
    PowerSupply p1("Corsair RM850x", 850, "80 PLUS Gold", false);
    PowerSupply p2("Corsair RM850x", 850, "80 PLUS Gold", false);
    PowerSupply p3("Seasonic 750", 750, "80 PLUS Gold", false);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_FALSE(oss.str().empty());
}