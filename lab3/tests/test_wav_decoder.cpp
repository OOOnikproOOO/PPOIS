/**
 * @file test_wav_decoder.cpp
 * @brief Unit tests for WAVDecoder class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "WAVDecoder.h"
#include "CorruptedAudioFileException.h"

TEST(WAVDecoderTest, ConstructorAndGetters) {
    WAVDecoder decoder(1, 441000);
    EXPECT_EQ(decoder.GetAudioFormatCode(), 1);
    EXPECT_EQ(decoder.GetDataChunkSizeBytes(), 441000);
    EXPECT_EQ(decoder.GetBytesRead(), 0);
    EXPECT_FALSE(decoder.IsRiffValid());
}

TEST(WAVDecoderTest, HeaderValidationAndExceptions) {
    WAVDecoder decoder(1, 1000);
    EXPECT_THROW(decoder.ParseRiffHeader(20), CorruptedAudioFileException);
    EXPECT_FALSE(decoder.IsRiffValid());

    EXPECT_NO_THROW(decoder.ParseRiffHeader(44));
    EXPECT_TRUE(decoder.IsRiffValid());
}

TEST(WAVDecoderTest, ReadPcmDataAndSampleCalculation) {
    WAVDecoder decoder(1, 4000);
    EXPECT_EQ(decoder.ReadPcmData(1000), 1000u);
    EXPECT_EQ(decoder.GetBytesRead(), 1000);

    EXPECT_EQ(decoder.CalculateTotalSamples(4), 1000u);
    EXPECT_EQ(decoder.CalculateTotalSamples(0), 0u);

    decoder.Reset();
    EXPECT_EQ(decoder.GetBytesRead(), 0);
    EXPECT_FALSE(decoder.IsRiffValid());
}

TEST(WAVDecoderTest, EqualityAndStream) {
    WAVDecoder d1(1, 2048);
    WAVDecoder d2(1, 2048);
    WAVDecoder d3(3, 2048);

    EXPECT_EQ(d1, d2);
    EXPECT_NE(d1, d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_FALSE(oss.str().empty());
}