/**
 * @file test_audio_recorder.cpp
 * @brief Unit tests for AudioRecorder class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioRecorder.h"

TEST(AudioRecorderTest, ConstructorAndGetters) {
    AudioRecorder rec(48000, 2048, false);
    EXPECT_EQ(rec.GetSampleRateHz(), 48000);
    EXPECT_DOUBLE_EQ(rec.GetRecordedSeconds(), 0.0);
    EXPECT_FALSE(rec.IsRecording());
    EXPECT_EQ(rec.GetBuffer().GetCapacity(), 2048u);
}

TEST(AudioRecorderTest, StartStopAndCapture) {
    AudioRecorder rec(1000, 100);
    AudioSample sample(0.5, 0.5, 16);

    EXPECT_FALSE(rec.CaptureSample(sample));

    rec.StartRecording();
    EXPECT_TRUE(rec.IsRecording());

    EXPECT_TRUE(rec.CaptureSample(sample));
    EXPECT_GT(rec.GetRecordedSeconds(), 0.0);
    EXPECT_EQ(rec.GetBuffer().GetAvailableSamplesCount(), 1u);

    rec.StopRecording();
    EXPECT_FALSE(rec.IsRecording());
    EXPECT_FALSE(rec.CaptureSample(sample));

    rec.Reset();
    EXPECT_DOUBLE_EQ(rec.GetRecordedSeconds(), 0.0);
    EXPECT_EQ(rec.GetBuffer().GetAvailableSamplesCount(), 0u);
}

TEST(AudioRecorderTest, EqualityAndStream) {
    AudioRecorder r1(44100, 100);
    AudioRecorder r2(44100, 100);
    AudioRecorder r3(48000, 100);

    EXPECT_EQ(r1, r2);
    EXPECT_NE(r1, r3);

    std::ostringstream oss;
    oss << r1;
    EXPECT_FALSE(oss.str().empty());
}