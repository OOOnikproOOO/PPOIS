/**
 * @file test_audio_fingerprint.cpp
 * @brief Unit tests for AudioFingerprint class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioFingerprint.h"

TEST(AudioFingerprintTest, ConstructorAndGetters) {
    AudioFingerprint fp("a1b2c3d4e5f60718", 2, 0.98, 15.0);
    EXPECT_EQ(fp.GetFingerprintHash(), "a1b2c3d4e5f60718");
    EXPECT_EQ(fp.GetAlgorithmVersion(), 2);
    EXPECT_DOUBLE_EQ(fp.GetConfidenceScore(), 0.98);
    EXPECT_DOUBLE_EQ(fp.GetDurationAnalyzedSec(), 15.0);
    EXPECT_TRUE(fp.IsValid());
}

TEST(AudioFingerprintTest, GenerateFromBufferAndMatch) {
    AudioFingerprint fp;
    EXPECT_FALSE(fp.IsValid());

    AudioBuffer buffer(128);
    for (int i = 0; i < 32; i++)
        buffer.WriteSample(AudioSample(0.5, 0.5, 16));

    fp.GenerateFromBuffer(buffer);
    EXPECT_TRUE(fp.IsValid());
    EXPECT_FALSE(fp.GetFingerprintHash().empty());

    AudioFingerprint copy = fp;
    EXPECT_DOUBLE_EQ(fp.MatchConfidence(copy), fp.GetConfidenceScore() * fp.GetConfidenceScore());

    AudioFingerprint different("0000000000000000", 1, 0.9);
    EXPECT_LT(fp.MatchConfidence(different), 1.0);

    fp.Clear();
    EXPECT_FALSE(fp.IsValid());
    EXPECT_DOUBLE_EQ(fp.MatchConfidence(different), 0.0);
}

TEST(AudioFingerprintTest, EqualityAndStream) {
    AudioFingerprint f1("hash123", 1, 0.95);
    AudioFingerprint f2("hash123", 1, 0.95);
    AudioFingerprint f3("hash456", 1, 0.95);

    EXPECT_EQ(f1, f2);
    EXPECT_NE(f1, f3);

    std::ostringstream oss;
    oss << f1;
    EXPECT_FALSE(oss.str().empty());
}