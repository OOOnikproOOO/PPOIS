/**
 * @file test_graphics_card.cpp
 * @brief Unit tests for the GraphicsCard class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "GraphicsCard.h"
#include "DeviceNotFoundException.h"
#include "MemoryAllocationException.h"

TEST(GraphicsCardTest, ConstructorAndGetters) {
    GraphicsCard gpu("GeForce RTX 4080", 320);
    EXPECT_EQ(gpu.GetModelName(), "GeForce RTX 4080");
    EXPECT_EQ(gpu.GetPortCount(), 0);
    EXPECT_GT(gpu.CalculateCurrentPowerDraw(), 0);
}

TEST(GraphicsCardTest, AddPortAndAccess) {
    GraphicsCard gpu("Radeon RX 7900 XTX", 355);
    gpu.AddPort(VideoPort("HDMI 2.1", 3840, 144));
    gpu.AddPort(VideoPort("DisplayPort 2.1", 7680, 165));
    EXPECT_EQ(gpu.GetPortCount(), 2);

    EXPECT_EQ(gpu.GetPort(0).GetPortType(), "HDMI 2.1");
    EXPECT_THROW(gpu.GetPort(5), DeviceNotFoundException);
}

TEST(GraphicsCardTest, RenderSceneAndVRAMAllocation) {
    GraphicsCard gpu("GeForce RTX 4070", 200, GPUCore(0, 2400), VRAM(12288, 192, "GDDR6X"));
    gpu.RenderScene(60, 2048);
    EXPECT_EQ(gpu.GetVRAM().GetUsedMb(), 2048);
    EXPECT_GT(gpu.GetGPUCore().GetLoadPercentage(), 0.0);
    EXPECT_GT(gpu.CalculateCurrentPowerDraw(), 30);

    gpu.RenderScene(0, 1024);
}

TEST(GraphicsCardTest, RenderSceneExceptionSafety) {
    GraphicsCard gpu("GeForce RTX 3060", 170, GPUCore(0, 1800), VRAM(8192, 128, "GDDR6"));
    // Requesting more VRAM than available throws MemoryAllocationException
    EXPECT_THROW(gpu.RenderScene(60, 16384), MemoryAllocationException);
}

TEST(GraphicsCardTest, EqualityAndStream) {
    GraphicsCard g1("Model A", 250);
    GraphicsCard g2("Model A", 250);
    GraphicsCard g3("Model B", 300);

    EXPECT_TRUE(g1 == g2);
    EXPECT_TRUE(g1 != g3);

    std::stringstream ss;
    ss << g1;
    EXPECT_NE(ss.str().find("GraphicsCard:"), std::string::npos);
}