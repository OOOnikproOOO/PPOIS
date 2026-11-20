/**
 * @file test_device_manager.cpp
 * @brief Unit tests for DeviceManager class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "DeviceManager.h"
#include "DeviceAudioOutputException.h"

TEST(DeviceManagerTest, ConstructorAndGetters) {
    DeviceManager dm(true);
    EXPECT_TRUE(dm.IsAutoSwitchOnConnect());
    EXPECT_EQ(dm.GetDevicesCount(), 0u);
    EXPECT_EQ(dm.GetActiveDeviceIndex(), -1);
    EXPECT_THROW(dm.GetActiveDevice(), DeviceAudioOutputException);
}

TEST(DeviceManagerTest, RegisterAndSelectDevice) {
    DeviceManager dm;
    AudioOutputDevice dev1("Speakers", "DEV_SPK", 2, true);
    AudioOutputDevice dev2("Headphones", "DEV_HP", 2, true);
    AudioOutputDevice dev3("Offline USB", "DEV_OFF", 2, false);

    dm.RegisterDevice(dev1);
    EXPECT_EQ(dm.GetActiveDevice().GetDeviceId(), "DEV_SPK");

    dm.RegisterDevice(dev2);
    EXPECT_EQ(dm.GetActiveDevice().GetDeviceId(), "DEV_HP");

    dm.SelectActiveDevice("DEV_SPK");
    EXPECT_EQ(dm.GetActiveDevice().GetDeviceId(), "DEV_SPK");

    dm.RegisterDevice(dev3);
    EXPECT_THROW(dm.SelectActiveDevice("DEV_OFF"), DeviceAudioOutputException);
    EXPECT_THROW(dm.SelectActiveDevice("NONEXISTENT"), DeviceAudioOutputException);
}

TEST(DeviceManagerTest, RemoveAndClear) {
    DeviceManager dm;
    dm.RegisterDevice(AudioOutputDevice("Speakers", "DEV_SPK", 2, true));
    dm.RegisterDevice(AudioOutputDevice("Headphones", "DEV_HP", 2, true));

    dm.RemoveDevice("DEV_HP");
    EXPECT_EQ(dm.GetDevicesCount(), 1u);
    EXPECT_EQ(dm.GetActiveDevice().GetDeviceId(), "DEV_SPK");

    dm.Clear();
    EXPECT_EQ(dm.GetDevicesCount(), 0u);
    EXPECT_EQ(dm.GetActiveDeviceIndex(), -1);
}

TEST(DeviceManagerTest, EqualityAndStream) {
    DeviceManager dm1(true);
    DeviceManager dm2(true);
    DeviceManager dm3(false);

    EXPECT_EQ(dm1, dm2);
    EXPECT_NE(dm1, dm3);

    std::ostringstream oss;
    oss << dm1;
    EXPECT_FALSE(oss.str().empty());
}