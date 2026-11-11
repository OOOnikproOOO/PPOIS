/**
 * @file test_chipset.cpp
 * @brief Unit tests for the Chipset class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Chipset.h"
#include "Exceptions.h"

TEST(ChipsetTest, ConstructorAndGetters) {
    Chipset chipset("Intel Z790", 40, 8, 12);
    EXPECT_EQ(chipset.GetModelName(), "Intel Z790");
    EXPECT_EQ(chipset.GetPcieLanes(), 40);
    EXPECT_EQ(chipset.GetSataPorts(), 8);
    EXPECT_EQ(chipset.GetUsbPorts(), 12);
}

TEST(ChipsetTest, AllocateAndReleasePcieLanes) {
    Chipset chipset("AMD B650", 36, 4, 10);
    chipset.AllocatePcieLanes(16);
    EXPECT_EQ(chipset.GetPcieLanes(), 20);

    EXPECT_THROW(chipset.AllocatePcieLanes(25), ComputerException);
    EXPECT_THROW(chipset.AllocatePcieLanes(0), ComputerException);

    chipset.ReleasePcieLanes(16);
    EXPECT_EQ(chipset.GetPcieLanes(), 36);
}

TEST(ChipsetTest, SupportsOverclocking) {
    Chipset z790("Intel Z790", 40, 8, 12);
    Chipset b650("AMD B650", 36, 4, 10);
    Chipset h610("Intel H610", 20, 4, 6);

    EXPECT_TRUE(z790.SupportsOverclocking());
    EXPECT_TRUE(b650.SupportsOverclocking());
    EXPECT_FALSE(h610.SupportsOverclocking());
}

TEST(ChipsetTest, EqualityAndStream) {
    Chipset c1("AMD B650", 36, 4, 10);
    Chipset c2("AMD B650", 36, 4, 10);
    Chipset c3("Intel Z790", 40, 8, 12);

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_TRUE(c1 != c3);

    std::ostringstream oss;
    oss << c1;
    EXPECT_FALSE(oss.str().empty());
}