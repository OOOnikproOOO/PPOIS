/**
 * @file test_audio_sample.cpp
 * @brief Unit tests for AudioSample class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioSample.h"

TEST(AudioSampleTest, ConstructorAndGetters) {
    AudioSample sample(0.5, -0.4, 24);
    EXPECT_DOUBLE_EQ(sample.GetLeftChannel(), 0.5);
    EXPECT_DOUBLE_EQ(sample.GetRightChannel(), -0.4);
    EXPECT_EQ(sample.GetBitDepth(), 24);
    EXPECT_FALSE(sample.IsClipped());
}

TEST(AudioSampleTest, AmplifyAndClipping) {
    AudioSample sample(0.4, 0.4, 16);
    sample.Amplify(2.0);
    EXPECT_DOUBLE_EQ(sample.GetLeftChannel(), 0.8);
    EXPECT_DOUBLE_EQ(sample.GetRightChannel(), 0.8);
    EXPECT_FALSE(sample.IsClipped());

    sample.Amplify(2.0);
    EXPECT_DOUBLE_EQ(sample.GetLeftChannel(), 1.0);
    EXPECT_TRUE(sample.IsClipped());
}

TEST(AudioSampleTest, MonoDownmixAndRms) {
    AudioSample sample(0.6, 0.2, 16);
    EXPECT_GT(sample.CalculatePowerRms(), 0.0);

    sample.ConvertToMono();
    EXPECT_DOUBLE_EQ(sample.GetLeftChannel(), 0.4);
    EXPECT_DOUBLE_EQ(sample.GetRightChannel(), 0.4);
}

TEST(AudioSampleTest, EqualityAndStream) {
    AudioSample s1(0.2, 0.3, 16);
    AudioSample s2(0.2, 0.3, 16);
    AudioSample s3(0.5, 0.3, 16);

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}