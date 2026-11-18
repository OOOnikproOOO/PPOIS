/**
 * @file test_flac_decoder.cpp
 * @brief Unit tests for FLACDecoder class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "FLACDecoder.h"
#include "CorruptedAudioFileException.h"

TEST(FLACDecoderTest, ConstructorAndGetters) {
    FLACDecoder decoder(8, 4096);
    EXPECT_EQ(decoder.GetCompressionLevel(), 8);
    EXPECT_EQ(decoder.GetBlockSizeSamples(), 4096);
    EXPECT_EQ(decoder.GetDecodedBlocksCount(), 0);
    EXPECT_FALSE(decoder.IsMd5Verified());
}

TEST(FLACDecoderTest, DecodeBlockAndCompressionRatio) {
    FLACDecoder decoder(5, 2048);
    EXPECT_EQ(decoder.DecodeBlock(0), 0u);
    EXPECT_EQ(decoder.DecodeBlock(1024), 2048u);
    EXPECT_EQ(decoder.GetDecodedBlocksCount(), 1);

    double ratio = decoder.CalculateCompressionRatio(1000, 600);
    EXPECT_DOUBLE_EQ(ratio, 40.0);
    EXPECT_DOUBLE_EQ(decoder.CalculateCompressionRatio(0, 100), 0.0);
}

TEST(FLACDecoderTest, ChecksumVerificationAndExceptions) {
    FLACDecoder decoder;
    EXPECT_NO_THROW(decoder.VerifyChecksum("abc123md5", "abc123md5"));
    EXPECT_TRUE(decoder.IsMd5Verified());

    EXPECT_THROW(decoder.VerifyChecksum("abc123md5", "wronghash"), CorruptedAudioFileException);
    EXPECT_FALSE(decoder.IsMd5Verified());

    decoder.Reset();
    EXPECT_EQ(decoder.GetDecodedBlocksCount(), 0);
    EXPECT_FALSE(decoder.IsMd5Verified());
}

TEST(FLACDecoderTest, EqualityAndStream) {
    FLACDecoder d1(5, 4096);
    FLACDecoder d2(5, 4096);
    FLACDecoder d3(8, 4096);

    EXPECT_EQ(d1, d2);
    EXPECT_NE(d1, d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_FALSE(oss.str().empty());
}