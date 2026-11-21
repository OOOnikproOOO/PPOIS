/**
 * @file test_audio_buffer.cpp
 * @brief Unit tests for AudioBuffer class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioBuffer.h"
#include "PlaybackBufferUnderflowException.h"

TEST(AudioBufferTest, ConstructorAndCapacity) {
    AudioBuffer buffer(512);
    EXPECT_EQ(buffer.GetCapacity(), 512);
    EXPECT_EQ(buffer.GetAvailableSamplesCount(), 0);
    EXPECT_DOUBLE_EQ(buffer.GetOccupancyPercentage(), 0.0);
    EXPECT_FALSE(buffer.IsUnderrun());
}

TEST(AudioBufferTest, WriteReadFIFO) {
    AudioBuffer buffer(4);
    AudioSample s1(0.1, 0.1, 16);
    AudioSample s2(0.2, 0.2, 16);

    EXPECT_TRUE(buffer.WriteSample(s1));
    EXPECT_TRUE(buffer.WriteSample(s2));
    EXPECT_EQ(buffer.GetAvailableSamplesCount(), 2);
    EXPECT_DOUBLE_EQ(buffer.GetOccupancyPercentage(), 50.0);

    AudioSample r1 = buffer.ReadSample();
    EXPECT_EQ(r1, s1);

    AudioSample r2 = buffer.ReadSample();
    EXPECT_EQ(r2, s2);

    EXPECT_EQ(buffer.GetAvailableSamplesCount(), 0);
}

TEST(AudioBufferTest, UnderflowException) {
    AudioBuffer buffer(2);
    EXPECT_THROW(buffer.ReadSample(), PlaybackBufferUnderflowException);
    EXPECT_TRUE(buffer.IsUnderrun());
}

TEST(AudioBufferTest, BufferFullAndClear) {
    AudioBuffer buffer(2);
    EXPECT_TRUE(buffer.WriteSample(AudioSample(0.1, 0.1, 16)));
    EXPECT_TRUE(buffer.WriteSample(AudioSample(0.2, 0.2, 16)));
    EXPECT_FALSE(buffer.WriteSample(AudioSample(0.3, 0.3, 16)));

    buffer.Clear();
    EXPECT_EQ(buffer.GetAvailableSamplesCount(), 0);
    EXPECT_DOUBLE_EQ(buffer.GetOccupancyPercentage(), 0.0);
}

TEST(AudioBufferTest, EqualityAndStream) {
    AudioBuffer b1(100);
    AudioBuffer b2(100);
    AudioBuffer b3(200);

    EXPECT_EQ(b1, b2);
    EXPECT_NE(b1, b3);

    std::ostringstream oss;
    oss << b1;
    EXPECT_FALSE(oss.str().empty());
}