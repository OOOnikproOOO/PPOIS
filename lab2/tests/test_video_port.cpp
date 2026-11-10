/**
 * @file test_video_port.cpp
 * @brief Unit tests for the VideoPort class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "VideoPort.h"

TEST(VideoPortTest, ConstructorAndGetters) {
    VideoPort port("HDMI 2.1", 3840, 144);
    EXPECT_EQ(port.GetPortType(), "HDMI 2.1");
    EXPECT_EQ(port.GetMaxResolutionWidth(), 3840);
    EXPECT_EQ(port.GetMaxRefreshRateHz(), 144);
    EXPECT_FALSE(port.IsConnected());
}

TEST(VideoPortTest, ConnectAndDisconnectCable) {
    VideoPort port("DisplayPort 1.4", 3840, 240);
    EXPECT_FALSE(port.IsConnected());

    port.ConnectCable();
    EXPECT_TRUE(port.IsConnected());

    port.DisconnectCable();
    EXPECT_FALSE(port.IsConnected());
}

TEST(VideoPortTest, SupportsDisplayMode) {
    VideoPort port("DisplayPort 1.4", 3840, 144);
    EXPECT_TRUE(port.SupportsDisplayMode(2560, 144));
    EXPECT_TRUE(port.SupportsDisplayMode(3840, 120));
    EXPECT_FALSE(port.SupportsDisplayMode(7680, 144));
    EXPECT_FALSE(port.SupportsDisplayMode(1920, 360));
    EXPECT_FALSE(port.SupportsDisplayMode(0, 144));
}

TEST(VideoPortTest, EqualityAndStream) {
    VideoPort p1("DisplayPort 1.4", 3840, 144);
    VideoPort p2("DisplayPort 1.4", 3840, 144);
    VideoPort p3("HDMI 2.0", 3840, 60);

    EXPECT_TRUE(p1 == p2);
    EXPECT_TRUE(p1 != p3);

    std::stringstream ss;
    ss << p1;
    EXPECT_NE(ss.str().find("VideoPort"), std::string::npos);
}