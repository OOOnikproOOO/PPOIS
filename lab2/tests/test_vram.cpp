/**
 * @file test_vram.cpp
 * @brief Unit tests for the VRAM class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "VRAM.h"
#include "MemoryAllocationException.h"

TEST(VRAMTest, ConstructorAndGetters) {
    VRAM vram(16384, 256, "GDDR6");
    EXPECT_EQ(vram.GetCapacityMb(), 16384);
    EXPECT_EQ(vram.GetBusWidthBits(), 256);
    EXPECT_EQ(vram.GetUsedMb(), 0);
    EXPECT_EQ(vram.GetMemoryType(), "GDDR6");
}

TEST(VRAMTest, AllocateAndFree) {
    VRAM vram(8192, 128, "GDDR6");
    EXPECT_FALSE(vram.Allocate(0));
    EXPECT_TRUE(vram.Allocate(4096));
    EXPECT_EQ(vram.GetUsedMb(), 4096);

    vram.Free(0);
    EXPECT_EQ(vram.GetUsedMb(), 4096);

    vram.Free(2048);
    EXPECT_EQ(vram.GetUsedMb(), 2048);

    vram.Free(10000);
    EXPECT_EQ(vram.GetUsedMb(), 0);
}

TEST(VRAMTest, OutOfMemoryException) {
    VRAM vram(4096, 128, "GDDR6");
    EXPECT_THROW(vram.Allocate(5000), MemoryAllocationException);
}

TEST(VRAMTest, CalculateBandwidth) {
    VRAM vram(16384, 256, "GDDR6X");
    double bw = vram.CalculateBandwidthGbps(2500);
    EXPECT_GT(bw, 100.0);

    EXPECT_DOUBLE_EQ(vram.CalculateBandwidthGbps(0), 0.0);
}

TEST(VRAMTest, EqualityAndStream) {
    VRAM v1(16384, 256, "GDDR6");
    VRAM v2(16384, 256, "GDDR6");
    VRAM v3(8192, 128, "GDDR6");

    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v1 != v3);

    std::stringstream ss;
    ss << v1;
    EXPECT_NE(ss.str().find("VRAM:"), std::string::npos);
}