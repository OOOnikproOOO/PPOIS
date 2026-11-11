/**
 * @file test_pcie_slot.cpp
 * @brief Unit tests for the PCIeSlot class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "PCIeSlot.h"
#include "Exceptions.h"

TEST(PCIeSlotTest, ConstructorAndGetters) {
    PCIeSlot slot(0, "PCIe 5.0", 16);
    EXPECT_EQ(slot.GetSlotIndex(), 0);
    EXPECT_EQ(slot.GetGeneration(), "PCIe 5.0");
    EXPECT_EQ(slot.GetLaneWidth(), 16);
    EXPECT_FALSE(slot.IsOccupied());
    EXPECT_TRUE(slot.GetInstalledDeviceName().empty());
}

TEST(PCIeSlotTest, InstallAndRemoveDevice) {
    PCIeSlot slot(0, "PCIe 4.0", 16);
    slot.InstallDevice("NVIDIA GeForce RTX 4080");
    EXPECT_TRUE(slot.IsOccupied());
    EXPECT_EQ(slot.GetInstalledDeviceName(), "NVIDIA GeForce RTX 4080");

    EXPECT_THROW(slot.InstallDevice("Another Device"), ComputerException);
    EXPECT_THROW(slot.InstallDevice(""), ComputerException);

    slot.RemoveDevice();
    EXPECT_FALSE(slot.IsOccupied());
    EXPECT_TRUE(slot.GetInstalledDeviceName().empty());

    EXPECT_THROW(slot.RemoveDevice(), DeviceNotFoundException);
}

TEST(PCIeSlotTest, CalculateBandwidthGBs) {
    PCIeSlot slotGen4(0, "PCIe 4.0", 16);
    PCIeSlot slotGen5(1, "PCIe 5.0", 16);
    PCIeSlot slotGen3(2, "PCIe 3.0", 4);

    EXPECT_NEAR(slotGen4.CalculateBandwidthGBs(), 1.969 * 16, 0.01);
    EXPECT_NEAR(slotGen5.CalculateBandwidthGBs(), 3.938 * 16, 0.01);
    EXPECT_NEAR(slotGen3.CalculateBandwidthGBs(), 0.985 * 4, 0.01);
}

TEST(PCIeSlotTest, EqualityAndStream) {
    PCIeSlot s1(0, "PCIe 4.0", 16);
    PCIeSlot s2(0, "PCIe 4.0", 16);
    PCIeSlot s3(1, "PCIe 4.0", 4);

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_TRUE(s1 != s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}