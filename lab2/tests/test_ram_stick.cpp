/**
 * @file test_ram_stick.cpp
 * @brief Unit tests for the RAMStick class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "RAMStick.h"
#include "MemoryAllocationException.h"

TEST(RAMStickTest, ConstructorAndGetters) {
    RAMStick stick("KF432C16BB/16", 16384, 3200, "DDR4");
    EXPECT_EQ(stick.GetSerialNumber(), "KF432C16BB/16");
    EXPECT_EQ(stick.GetCapacityMb(), 16384);
    EXPECT_EQ(stick.GetFrequencyMhz(), 3200);
    EXPECT_EQ(stick.GetGeneration(), "DDR4");
    EXPECT_FALSE(stick.IsXmpEnabled());
    EXPECT_EQ(stick.GetUsedMb(), 0);
    EXPECT_TRUE(stick.RunDiagnostics());
}

TEST(RAMStickTest, WriteReadAndMemoryClear) {
    RAMStick stick("SN-001", 8192);
    EXPECT_FALSE(stick.WriteData(0));
    EXPECT_TRUE(stick.WriteData(4096));
    EXPECT_EQ(stick.GetUsedMb(), 4096);
    EXPECT_TRUE(stick.ReadData(2048));
    EXPECT_FALSE(stick.ReadData(5000));

    stick.ClearMemory();
    EXPECT_EQ(stick.GetUsedMb(), 0);
    EXPECT_FALSE(stick.ReadData(100));
}

TEST(RAMStickTest, MemoryAllocationExceptionOnOverflow) {
    RAMStick stick("SN-002", 4096);
    EXPECT_TRUE(stick.WriteData(4000));
    EXPECT_THROW(stick.WriteData(500), MemoryAllocationException);
}

TEST(RAMStickTest, EnableXMP) {
    RAMStick stick("SN-003", 16384, 2666, "DDR4");
    RAMTiming xmp_timing(16, 18, 18, 36);
    stick.EnableXMP(3600, xmp_timing);

    EXPECT_TRUE(stick.IsXmpEnabled());
    EXPECT_EQ(stick.GetFrequencyMhz(), 3600);
    EXPECT_EQ(stick.GetTimings().GetCasLatency(), 16);
}

TEST(RAMStickTest, EqualityAndStream) {
    RAMStick s1("SN-A", 8192, 3200, "DDR4");
    RAMStick s2("SN-A", 8192, 3200, "DDR4");
    RAMStick s3("SN-B", 16384, 5600, "DDR5");

    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s1 != s3);

    std::stringstream ss;
    ss << s1;
    EXPECT_NE(ss.str().find("DDR4 8192 MB"), std::string::npos);
}