/**
 * @file test_audio_codec.cpp
 * @brief Unit tests for AudioCodec class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioCodec.h"
#include "UnsupportedAudioFormatException.h"

TEST(AudioCodecTest, ConstructorAndGetters) {
    AudioCodec codec("FLAC", 1000, 96000, 2, true);
    EXPECT_EQ(codec.GetCodecName(), "FLAC");
    EXPECT_EQ(codec.GetBitrateKbps(), 1000);
    EXPECT_EQ(codec.GetSampleRateHz(), 96000);
    EXPECT_EQ(codec.GetChannelsCount(), 2);
    EXPECT_TRUE(codec.IsLossless());
}

TEST(AudioCodecTest, BitrateAndFileSizeEstimation) {
    AudioCodec codec("MP3", 320, 44100, 2, false);
    EXPECT_EQ(codec.CalculateBytesPerSecond(), 40000u);
    EXPECT_GT(codec.EstimateFileSizeMb(180.0), 0.0);
    EXPECT_DOUBLE_EQ(codec.EstimateFileSizeMb(0.0), 0.0);

    codec.SetBitrate(256);
    EXPECT_EQ(codec.GetBitrateKbps(), 256);
    codec.SetBitrate(10);
    EXPECT_EQ(codec.GetBitrateKbps(), 256);
}

TEST(AudioCodecTest, ValidationAndExceptions) {
    AudioCodec valid("AAC", 192, 48000, 2, false);
    EXPECT_NO_THROW(valid.ValidateParameters());

    AudioCodec invalidRate("WAV", 1411, 2000, 2, true);
    EXPECT_THROW(invalidRate.ValidateParameters(), UnsupportedAudioFormatException);

    AudioCodec invalidChannels("FLAC", 800, 44100, 0, true);
    EXPECT_THROW(invalidChannels.ValidateParameters(), UnsupportedAudioFormatException);
}

TEST(AudioCodecTest, EqualityAndStream) {
    AudioCodec c1("MP3", 320, 44100, 2, false);
    AudioCodec c2("MP3", 320, 44100, 2, false);
    AudioCodec c3("FLAC", 320, 44100, 2, true);

    EXPECT_EQ(c1, c2);
    EXPECT_NE(c1, c3);

    std::ostringstream oss;
    oss << c1;
    EXPECT_FALSE(oss.str().empty());
}