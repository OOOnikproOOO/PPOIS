/**
 * @file test_mp3_decoder.cpp
 * @brief Unit tests for MP3Decoder class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "MP3Decoder.h"

TEST(MP3DecoderTest, ConstructorAndGetters) {
    MP3Decoder decoder(true, 2, 417);
    EXPECT_TRUE(decoder.IsVbr());
    EXPECT_EQ(decoder.GetId3Version(), 2);
    EXPECT_EQ(decoder.GetFrameSizeBytes(), 417);
    EXPECT_EQ(decoder.GetDecodedFramesCount(), 0);
}

TEST(MP3DecoderTest, DecodeFrameAndDuration) {
    MP3Decoder decoder(false, 2, 417);
    EXPECT_EQ(decoder.DecodeFrame(100), 0u);
    EXPECT_EQ(decoder.DecodeFrame(500), 1152u);
    EXPECT_EQ(decoder.GetDecodedFramesCount(), 1);

    double duration = decoder.CalculateDecodedDurationSec(1000000, 320);
    EXPECT_GT(duration, 0.0);
    EXPECT_DOUBLE_EQ(decoder.CalculateDecodedDurationSec(1000, 0), 0.0);

    decoder.ResetDecoder();
    EXPECT_EQ(decoder.GetDecodedFramesCount(), 0);
}

TEST(MP3DecoderTest, ParseHeader) {
    MP3Decoder decoder;
    EXPECT_TRUE(decoder.ParseHeader(128));
    EXPECT_FALSE(decoder.ParseHeader(4));
}

TEST(MP3DecoderTest, EqualityAndStream) {
    MP3Decoder d1(false, 2, 417);
    MP3Decoder d2(false, 2, 417);
    MP3Decoder d3(true, 2, 417);

    EXPECT_EQ(d1, d2);
    EXPECT_NE(d1, d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_FALSE(oss.str().empty());
}