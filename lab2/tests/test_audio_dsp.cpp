/**
 * @file test_audio_dsp.cpp
 * @brief Unit tests for the AudioDSP class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioDSP.h"
#include "ComputerException.h"

TEST(AudioDSPTest, ConstructorAndGetters) {
    AudioDSP dsp("Flat", 2, 0.0);
    EXPECT_EQ(dsp.GetProfileName(), "Flat");
    EXPECT_EQ(dsp.GetLatencyMs(), 2);
    EXPECT_DOUBLE_EQ(dsp.GetGainDb(), 0.0);
    EXPECT_TRUE(dsp.IsEqualizerEnabled());
}

TEST(AudioDSPTest, SoundProfileAndExceptions) {
    AudioDSP dsp;
    dsp.ApplySoundProfile("Bass Boost");
    EXPECT_EQ(dsp.GetProfileName(), "Bass Boost");

    EXPECT_THROW(dsp.ApplySoundProfile(""), ComputerException);
}

TEST(AudioDSPTest, SetGainAndExceptions) {
    AudioDSP dsp;
    dsp.SetGain(3.5);
    EXPECT_DOUBLE_EQ(dsp.GetGainDb(), 3.5);

    EXPECT_THROW(dsp.SetGain(-70.0), ComputerException);
    EXPECT_THROW(dsp.SetGain(20.0), ComputerException);
}

TEST(AudioDSPTest, ToggleEqualizer) {
    AudioDSP dsp;
    EXPECT_TRUE(dsp.IsEqualizerEnabled());

    dsp.ToggleEqualizer(false);
    EXPECT_FALSE(dsp.IsEqualizerEnabled());
}

TEST(AudioDSPTest, EqualityAndStream) {
    AudioDSP d1("Preset", 2, 0.0);
    AudioDSP d2("Preset", 2, 0.0);
    AudioDSP d3("Other", 5, 2.0);

    EXPECT_TRUE(d1 == d2);
    EXPECT_TRUE(d1 != d3);

    std::stringstream ss;
    ss << d1;
    EXPECT_NE(ss.str().find("AudioDSP"), std::string::npos);
}