/**
 * @file test_ram.cpp
 * @brief Unit tests for the RAM class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "RAM.h"
#include "Exceptions.h"

TEST(RAMTest, ConstructorAndDefaultState) {
    RAM ram(4);
    EXPECT_EQ(ram.GetMaxSlots(), 4);
    EXPECT_EQ(ram.GetInstalledSticksCount(), 0);
    EXPECT_EQ(ram.GetTotalCapacityMb(), 0);
    EXPECT_EQ(ram.GetChannelMode(), 1);
    EXPECT_EQ(ram.GetTotalAllocatedMb(), 0);
}

TEST(RAMTest, InstallAndRemoveSticksChannelScaling) {
    RAM ram(4);
    RAMStick s1("S1", 8192, 3200, "DDR4");
    RAMStick s2("S2", 8192, 3200, "DDR4");
    RAMStick s3("S3", 8192, 3200, "DDR4");
    RAMStick s4("S4", 8192, 3200, "DDR4");

    ram.InstallStick(s1, 0);
    EXPECT_EQ(ram.GetChannelMode(), 1);
    EXPECT_EQ(ram.GetTotalCapacityMb(), 8192);

    ram.InstallStick(s2, 1);
    EXPECT_EQ(ram.GetChannelMode(), 2);

    ram.InstallStick(s3, 2);
    ram.InstallStick(s4, 3);
    EXPECT_EQ(ram.GetChannelMode(), 4);
    EXPECT_EQ(ram.GetTotalCapacityMb(), 32768);

    RAMStick removed = ram.RemoveStick(0);
    EXPECT_EQ(removed.GetSerialNumber(), "S1");
    EXPECT_EQ(ram.GetChannelMode(), 2);
}

TEST(RAMTest, InstallExceptions) {
    RAM ram(2);
    RAMStick ddr4("S1", 8192, 3200, "DDR4");
    RAMStick ddr5("S2", 16384, 5600, "DDR5");

    EXPECT_THROW(ram.InstallStick(ddr4, 5), ComputerException);

    ram.InstallStick(ddr4, 0);
    EXPECT_THROW(ram.InstallStick(ddr5, 1), IncompatibleMemoryException);

    EXPECT_THROW(ram.RemoveStick(5), DeviceNotFoundException);
}

TEST(RAMTest, AllocateAndFreeMemory) {
    RAM ram(2);
    ram.InstallStick(RAMStick("S1", 8192), 0);

    EXPECT_FALSE(ram.Allocate(0));
    EXPECT_TRUE(ram.Allocate(4096));
    EXPECT_EQ(ram.GetTotalAllocatedMb(), 4096);

    EXPECT_THROW(ram.Allocate(5000), MemoryAllocationException);

    ram.Free(0);
    EXPECT_EQ(ram.GetTotalAllocatedMb(), 4096);

    ram.Free(2048);
    EXPECT_EQ(ram.GetTotalAllocatedMb(), 2048);

    ram.Free(10000);
    EXPECT_EQ(ram.GetTotalAllocatedMb(), 0);
}

TEST(RAMTest, EqualityAndStream) {
    RAM r1(4);
    RAM r2(4);
    RAM r3(2);

    EXPECT_TRUE(r1 == r2);
    EXPECT_TRUE(r1 != r3);

    std::stringstream ss;
    ss << r1;
    EXPECT_NE(ss.str().find("RAM Subsystem"), std::string::npos);
}

TEST(RAMTest, GetStickAndExceptions) {
    RAM ram(2);
    ram.InstallStick(RAMStick("S1", 8192, 3200, "DDR4"), 0);
    EXPECT_EQ(ram.GetStick(0).GetSerialNumber(), "S1");
    EXPECT_THROW(ram.GetStick(1), DeviceNotFoundException);
    EXPECT_THROW(ram.GetStick(-1), DeviceNotFoundException);
}