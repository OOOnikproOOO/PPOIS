/**
 * @file test_display.cpp
 * @brief Unit tests for the Display class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Display.h"
#include "Exceptions.h"

TEST(DisplayTest, ConstructorAndGetters) {
    Display display("Dell UltraSharp", 3840, 2160, 60);
    EXPECT_EQ(display.GetModel(), "Dell UltraSharp");
    EXPECT_EQ(display.GetResolutionWidth(), 3840);
    EXPECT_EQ(display.GetResolutionHeight(), 2160);
    EXPECT_EQ(display.GetRefreshRateHz(), 60);
    EXPECT_TRUE(display.IsPoweredOn());
}

TEST(DisplayTest, PowerToggle) {
    Display display;
    EXPECT_TRUE(display.IsPoweredOn());

    display.PowerToggle();
    EXPECT_FALSE(display.IsPoweredOn());

    display.PowerToggle();
    EXPECT_TRUE(display.IsPoweredOn());
}

TEST(DisplayTest, SetResolutionAndRefreshRate) {
    Display display;
    display.SetResolution(1920, 1080);
    EXPECT_EQ(display.GetResolutionWidth(), 1920);
    EXPECT_EQ(display.GetResolutionHeight(), 1080);

    display.SetRefreshRate(240);
    EXPECT_EQ(display.GetRefreshRateHz(), 240);

    EXPECT_THROW(display.SetResolution(100, 1080), ComputerException);
    EXPECT_THROW(display.SetResolution(1920, 100), ComputerException);
    EXPECT_THROW(display.SetRefreshRate(10), ComputerException);
    EXPECT_THROW(display.SetRefreshRate(1000), ComputerException);
}

TEST(DisplayTest, CalculateTotalPixels) {
    Display display("Monitor", 1920, 1080, 60);
    EXPECT_EQ(display.CalculateTotalPixels(), 1920LL * 1080LL);
}

TEST(DisplayTest, EqualityAndStream) {
    Display d1("LG", 2560, 1440, 144);
    Display d2("LG", 2560, 1440, 144);
    Display d3("Samsung", 1920, 1080, 60);

    EXPECT_TRUE(d1 == d2);
    EXPECT_TRUE(d1 != d3);

    std::stringstream ss;
    ss << d1;
    EXPECT_NE(ss.str().find("Display:"), std::string::npos);
}