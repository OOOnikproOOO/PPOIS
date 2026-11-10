/**
 * @file test_speaker_system.cpp
 * @brief Unit tests for the SpeakerSystem class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "SpeakerSystem.h"
#include "Exceptions.h"

TEST(SpeakerSystemTest, ConstructorAndGetters) {
    SpeakerSystem spk("Edifier R1280DB", 42, 40);
    EXPECT_EQ(spk.GetSystemName(), "Edifier R1280DB");
    EXPECT_EQ(spk.GetPowerWattsRms(), 42);
    EXPECT_EQ(spk.GetCurrentVolume(), 40);
    EXPECT_FALSE(spk.IsMuted());
}

TEST(SpeakerSystemTest, SetVolumeAndExceptions) {
    SpeakerSystem spk;
    spk.SetVolume(75);
    EXPECT_EQ(spk.GetCurrentVolume(), 75);

    EXPECT_THROW(spk.SetVolume(-5), ComputerException);
    EXPECT_THROW(spk.SetVolume(105), ComputerException);
}

TEST(SpeakerSystemTest, ToggleMuteAndOutputSound) {
    SpeakerSystem spk("Logitech", 50, 50);
    EXPECT_TRUE(spk.OutputSound(5, 70.0));
    EXPECT_FALSE(spk.OutputSound(0, 70.0));

    spk.ToggleMute();
    EXPECT_TRUE(spk.IsMuted());
    EXPECT_FALSE(spk.OutputSound(5, 70.0));

    spk.ToggleMute();
    EXPECT_FALSE(spk.IsMuted());

    spk.SetVolume(0);
    EXPECT_FALSE(spk.OutputSound(5, 70.0));

    spk.SetVolume(50);
    EXPECT_THROW(spk.OutputSound(5, 130.0), ComputerException);
}

TEST(SpeakerSystemTest, EqualityAndStream) {
    SpeakerSystem s1("Edifier", 40, 30);
    SpeakerSystem s2("Edifier", 40, 30);
    SpeakerSystem s3("Creative", 60, 50);

    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s1 != s3);

    std::stringstream ss;
    ss << s1;
    EXPECT_NE(ss.str().find("SpeakerSystem:"), std::string::npos);
}