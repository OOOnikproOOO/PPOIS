/**
 * @file test_audio_dac.cpp
 * @brief Unit tests for the AudioDAC class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioDAC.h"
#include "ComputerException.h"

TEST(AudioDACTest, ConstructorAndGetters) {
    AudioDAC dac(48000, 24, 115.0);
    EXPECT_EQ(dac.GetSamplingRateHz(), 48000);
    EXPECT_EQ(dac.GetBitDepth(), 24);
    EXPECT_DOUBLE_EQ(dac.GetSnrDb(), 115.0);
    EXPECT_TRUE(dac.IsActive());
}

TEST(AudioDACTest, ConvertDigitalToAnalog) {
    AudioDAC dac;
    EXPECT_TRUE(dac.ConvertDigitalToAnalog(44100));
    EXPECT_FALSE(dac.ConvertDigitalToAnalog(0));
    EXPECT_FALSE(dac.ConvertDigitalToAnalog(-100));
}

TEST(AudioDACTest, SetFormatAndExceptions) {
    AudioDAC dac;
    dac.SetFormat(96000, 24);
    EXPECT_EQ(dac.GetSamplingRateHz(), 96000);
    EXPECT_EQ(dac.GetBitDepth(), 24);

    EXPECT_THROW(dac.SetFormat(1000, 24), ComputerException);
    EXPECT_THROW(dac.SetFormat(48000, 20), ComputerException);
}

TEST(AudioDACTest, DynamicRangeCalculation) {
    AudioDAC dac(44100, 16, 98.0);
    EXPECT_DOUBLE_EQ(dac.CalculateDynamicRangeDb(), 16 * 6.02);
}

TEST(AudioDACTest, EqualityAndStream) {
    AudioDAC d1(48000, 24, 115.0);
    AudioDAC d2(48000, 24, 115.0);
    AudioDAC d3(44100, 16, 98.0);

    EXPECT_TRUE(d1 == d2);
    EXPECT_TRUE(d1 != d3);

    std::stringstream ss;
    ss << d1;
    EXPECT_NE(ss.str().find("AudioDAC"), std::string::npos);
}