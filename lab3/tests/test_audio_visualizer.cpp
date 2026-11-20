/**
 * @file test_audio_visualizer.cpp
 * @brief Unit tests for AudioVisualizer class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioVisualizer.h"

TEST(AudioVisualizerTest, ConstructorAndGetters) {
    AudioVisualizer viz("VU_Meter", 60);
    EXPECT_EQ(viz.GetMode(), "VU_Meter");
    EXPECT_EQ(viz.GetRefreshRateHz(), 60);
    EXPECT_DOUBLE_EQ(viz.GetLeftPeak(), 0.0);
    EXPECT_DOUBLE_EQ(viz.GetRightPeak(), 0.0);
}

TEST(AudioVisualizerTest, UpdateLevelsAndClamping) {
    AudioVisualizer viz;
    viz.UpdateLevels(AudioSample(0.6, 0.8, 16));
    EXPECT_DOUBLE_EQ(viz.GetLeftPeak(), 0.6);
    EXPECT_DOUBLE_EQ(viz.GetRightPeak(), 0.8);

    viz.UpdateLevels(AudioSample(0.2, 0.4, 16));
    EXPECT_DOUBLE_EQ(viz.GetLeftPeak(), 0.6);

    viz.UpdateLevels(AudioSample(1.5, -2.0, 16));
    EXPECT_DOUBLE_EQ(viz.GetLeftPeak(), 1.0);
    EXPECT_DOUBLE_EQ(viz.GetRightPeak(), 1.0);

    viz.ResetPeaks();
    EXPECT_DOUBLE_EQ(viz.GetLeftPeak(), 0.0);
    EXPECT_DOUBLE_EQ(viz.GetRightPeak(), 0.0);
}

TEST(AudioVisualizerTest, RenderAsciiBarAndVuMeter) {
    AudioVisualizer viz;
    std::string bar = viz.RenderAsciiBar(0.5, 10);
    EXPECT_EQ(bar.front(), '[');
    EXPECT_EQ(bar.back(), ']');
    EXPECT_EQ(bar.length(), 12u);

    viz.UpdateLevels(AudioSample(0.4, 0.7, 16));
    std::string vu = viz.RenderStereoVuMeter();
    EXPECT_NE(vu.find("L:"), std::string::npos);
    EXPECT_NE(vu.find("R:"), std::string::npos);
}

TEST(AudioVisualizerTest, SetModeAndLimits) {
    AudioVisualizer viz("Waveform", 200);
    EXPECT_EQ(viz.GetRefreshRateHz(), 120);

    viz.SetMode("SpectrumBars");
    EXPECT_EQ(viz.GetMode(), "SpectrumBars");
}

TEST(AudioVisualizerTest, EqualityAndStream) {
    AudioVisualizer v1("VU_Meter", 60);
    AudioVisualizer v2("VU_Meter", 60);
    AudioVisualizer v3("Waveform", 60);

    EXPECT_EQ(v1, v2);
    EXPECT_NE(v1, v3);

    std::ostringstream oss;
    oss << v1;
    EXPECT_FALSE(oss.str().empty());
}