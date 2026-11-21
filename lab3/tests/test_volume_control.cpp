/**
 * @file test_volume_control.cpp
 * @brief Unit tests for VolumeControl class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "VolumeControl.h"

TEST(VolumeControlTest, ConstructorAndGetters) {
    VolumeControl vc(80, false, 90);
    EXPECT_EQ(vc.GetVolumeLevel(), 80);
    EXPECT_FALSE(vc.IsMuted());
    EXPECT_EQ(vc.GetMaxLimit(), 90);
    EXPECT_EQ(vc.GetEffectiveVolume(), 80);
}

TEST(VolumeControlTest, SetVolumeAndLimits) {
    VolumeControl vc(50, false, 85);
    vc.SetVolume(100);
    EXPECT_EQ(vc.GetVolumeLevel(), 85);

    vc.SetVolume(-20);
    EXPECT_EQ(vc.GetVolumeLevel(), 0);

    vc.SetMaxLimit(70);
    EXPECT_EQ(vc.GetVolumeLevel(), 0);
}

TEST(VolumeControlTest, MuteAndRestore) {
    VolumeControl vc(75);
    vc.ToggleMute();
    EXPECT_TRUE(vc.IsMuted());
    EXPECT_EQ(vc.GetEffectiveVolume(), 0);

    vc.ToggleMute();
    EXPECT_FALSE(vc.IsMuted());
    EXPECT_EQ(vc.GetEffectiveVolume(), 75);

    vc.Reset();
    EXPECT_EQ(vc.GetVolumeLevel(), 50);
}

TEST(VolumeControlTest, GainCalculation) {
    VolumeControl vc(100);
    EXPECT_NEAR(vc.CalculateGainDecibels(), 0.0, 0.1);

    vc.SetVolume(0);
    EXPECT_DOUBLE_EQ(vc.CalculateGainDecibels(), -60.0);
}

TEST(VolumeControlTest, EqualityAndStream) {
    VolumeControl v1(50);
    VolumeControl v2(50);
    VolumeControl v3(80);

    EXPECT_EQ(v1, v2);
    EXPECT_NE(v1, v3);

    std::ostringstream oss;
    oss << v1;
    EXPECT_FALSE(oss.str().empty());
}