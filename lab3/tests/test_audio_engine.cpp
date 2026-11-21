/**
 * @file test_audio_engine.cpp
 * @brief Unit tests for AudioEngine class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioEngine.h"

TEST(AudioEngineTest, ConstructorAndGetters) {
    AudioEngine engine(48000, 1024);
    EXPECT_EQ(engine.GetState(), "Stopped");
    EXPECT_EQ(engine.GetSampleRateHz(), 48000);
    EXPECT_EQ(engine.GetBufferUnderrunsCount(), 0);
}

TEST(AudioEngineTest, PlaybackStateTransitions) {
    AudioEngine engine;
    EXPECT_EQ(engine.GetState(), "Stopped");

    engine.Play();
    EXPECT_EQ(engine.GetState(), "Playing");

    engine.Pause();
    EXPECT_EQ(engine.GetState(), "Paused");

    engine.Stop();
    EXPECT_EQ(engine.GetState(), "Stopped");
}

TEST(AudioEngineTest, RenderBufferAndUnderruns) {
    AudioEngine engine(44100, 10);
    engine.Play();

    engine.GetBuffer().WriteSample(AudioSample(0.1, 0.1, 16));
    engine.GetBuffer().WriteSample(AudioSample(0.2, 0.2, 16));

    size_t rendered = engine.RenderAudioBuffer(5);
    EXPECT_EQ(rendered, 2u);
    EXPECT_EQ(engine.GetBufferUnderrunsCount(), 1);

    engine.ResetEngine();
    EXPECT_EQ(engine.GetState(), "Stopped");
    EXPECT_EQ(engine.GetBufferUnderrunsCount(), 0);
}

TEST(AudioEngineTest, EqualityAndStream) {
    AudioEngine e1(44100, 100);
    AudioEngine e2(44100, 100);
    AudioEngine e3(48000, 100);

    EXPECT_EQ(e1, e2);
    EXPECT_NE(e1, e3);

    std::ostringstream oss;
    oss << e1;
    EXPECT_FALSE(oss.str().empty());
}