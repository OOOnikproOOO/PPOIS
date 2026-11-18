/**
 * @file test_audio_stream.cpp
 * @brief Unit tests for AudioStream class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioStream.h"

TEST(AudioStreamTest, ConstructorAndGetters) {
    AudioStream stream("https://stream.radio.fm/live", 300.0, 1024);
    EXPECT_EQ(stream.GetStreamSource(), "https://stream.radio.fm/live");
    EXPECT_DOUBLE_EQ(stream.GetTotalDurationSec(), 300.0);
    EXPECT_DOUBLE_EQ(stream.GetCurrentPositionSec(), 0.0);
    EXPECT_FALSE(stream.IsEof());
    EXPECT_DOUBLE_EQ(stream.GetRemainingTimeSec(), 300.0);
}

TEST(AudioStreamTest, ReadChunkAndEof) {
    AudioStream stream("file.mp3", 0.1, 100);
    EXPECT_GT(stream.ReadNextChunk(10), 0u);
    EXPECT_GT(stream.GetCurrentPositionSec(), 0.0);

    stream.ReadNextChunk(10);
    stream.ReadNextChunk(10);
    EXPECT_TRUE(stream.IsEof());
    EXPECT_DOUBLE_EQ(stream.GetRemainingTimeSec(), 0.0);
    EXPECT_EQ(stream.ReadNextChunk(10), 0u);
}

TEST(AudioStreamTest, SeekAndReset) {
    AudioStream stream("file.mp3", 200.0, 100);
    stream.Seek(50.0);
    EXPECT_DOUBLE_EQ(stream.GetCurrentPositionSec(), 50.0);
    EXPECT_FALSE(stream.IsEof());

    stream.Seek(-10.0);
    EXPECT_DOUBLE_EQ(stream.GetCurrentPositionSec(), 0.0);

    stream.Seek(500.0);
    EXPECT_DOUBLE_EQ(stream.GetCurrentPositionSec(), 200.0);
    EXPECT_TRUE(stream.IsEof());

    stream.ResetStream();
    EXPECT_DOUBLE_EQ(stream.GetCurrentPositionSec(), 0.0);
    EXPECT_FALSE(stream.IsEof());
}

TEST(AudioStreamTest, EqualityAndStream) {
    AudioStream s1("file.mp3", 100.0, 50);
    AudioStream s2("file.mp3", 100.0, 50);
    AudioStream s3("other.mp3", 100.0, 50);

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_FALSE(oss.str().empty());
}