/**
 * @file test_audio_output_device.cpp
 * @brief Unit tests for AudioOutputDevice class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioOutputDevice.h"

TEST(AudioOutputDeviceTest, ConstructorAndGetters) {
    AudioOutputDevice dev("Sony WH-1000XM4", "DEV_BT_01", 2, true, true);
    EXPECT_EQ(dev.GetDeviceName(), "Sony WH-1000XM4");
    EXPECT_EQ(dev.GetDeviceId(), "DEV_BT_01");
    EXPECT_EQ(dev.GetChannelsCount(), 2);
    EXPECT_TRUE(dev.IsConnected());
    EXPECT_TRUE(dev.IsDefault());
}

TEST(AudioOutputDeviceTest, ConnectDisconnectAndDefault) {
    AudioOutputDevice dev("Surround Sound", "DEV_SPK_01", 6, false, false);
    EXPECT_FALSE(dev.IsConnected());

    dev.Connect();
    EXPECT_TRUE(dev.IsConnected());

    dev.SetDefault(true);
    EXPECT_TRUE(dev.IsDefault());

    dev.Disconnect();
    EXPECT_FALSE(dev.IsConnected());
    EXPECT_FALSE(dev.IsDefault());
}

TEST(AudioOutputDeviceTest, FormattingAndChannelClamping) {
    AudioOutputDevice dev("Mono Speaker", "DEV_MONO", 0);
    EXPECT_EQ(dev.GetChannelsCount(), 1);

    std::string info = dev.FormatDeviceInfo();
    EXPECT_NE(info.find("DEV_MONO"), std::string::npos);
}

TEST(AudioOutputDeviceTest, EqualityAndStream) {
    AudioOutputDevice d1("Dev A", "ID_SAME");
    AudioOutputDevice d2("Dev B", "ID_SAME");
    AudioOutputDevice d3("Dev C", "ID_DIFFERENT");

    EXPECT_EQ(d1, d2);
    EXPECT_NE(d1, d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_FALSE(oss.str().empty());
}