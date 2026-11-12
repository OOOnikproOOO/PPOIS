/**
 * @file test_motherboard.cpp
 * @brief Unit tests for the Motherboard class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Motherboard.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"
#include "POSTFailureException.h"

TEST(MotherboardTest, ConstructorAndGetters) {
    VRM vrm(16, 1.25, 40.0, 92.0);
    Chipset chipset("AMD B650", 36, 4, 10);
    Motherboard mb("ASUS ROG STRIX B650-E", "ATX", "v1.40", vrm, chipset);

    EXPECT_EQ(mb.GetModelName(), "ASUS ROG STRIX B650-E");
    EXPECT_EQ(mb.GetFormFactor(), "ATX");
    EXPECT_EQ(mb.GetBiosVersion(), "v1.40");
    EXPECT_EQ(mb.GetSlotCount(), 0);
    EXPECT_EQ(mb.GetVRM().GetPhaseCount(), 16);
    EXPECT_EQ(mb.GetChipset().GetModelName(), "AMD B650");
}

TEST(MotherboardTest, AddSlotAndSlotAccess) {
    Motherboard mb;
    mb.AddSlot(PCIeSlot(0, "PCIe 5.0", 16));
    mb.AddSlot(PCIeSlot(1, "PCIe 4.0", 4));

    EXPECT_EQ(mb.GetSlotCount(), 2);
    EXPECT_EQ(mb.GetSlot(0).GetLaneWidth(), 16);
    EXPECT_EQ(mb.GetSlot(1).GetLaneWidth(), 4);

    EXPECT_THROW(mb.GetSlot(-1), DeviceNotFoundException);
    EXPECT_THROW(mb.GetSlot(2), DeviceNotFoundException);
}

TEST(MotherboardTest, FlashBios) {
    Motherboard mb;
    mb.FlashBios("v2.00Beta");
    EXPECT_EQ(mb.GetBiosVersion(), "v2.00Beta");

    EXPECT_THROW(mb.FlashBios(""), ComputerException);
}

TEST(MotherboardTest, PerformPOSTAndFailure) {
    Motherboard mb;
    EXPECT_TRUE(mb.PerformPOST());

    mb.GetVRM().SupplyCurrent(100.0);
    VRM overheatedVRM(16, 1.25, 108.0, 90.0);
    Motherboard hotMb("MSI MAG B650", "ATX", "v1.0", overheatedVRM, Chipset());
    EXPECT_THROW(hotMb.PerformPOST(), POSTFailureException);
}

TEST(MotherboardTest, EqualityAndStream) {
    Motherboard m1("ASUS ROG B650", "ATX", "v1.0");
    Motherboard m2("ASUS ROG B650", "ATX", "v1.0");
    Motherboard m3("MSI B650", "Micro-ATX", "v1.0");

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
    EXPECT_TRUE(m1 != m3);

    std::ostringstream oss;
    oss << m1;
    EXPECT_FALSE(oss.str().empty());
}