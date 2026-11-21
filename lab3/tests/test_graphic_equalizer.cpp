/**
 * @file test_graphic_equalizer.cpp
 * @brief Unit tests for GraphicEqualizer class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "GraphicEqualizer.h"
#include "InvalidEqualizerBandException.h"

TEST(GraphicEqualizerTest, ConstructorAndInitialization) {
    GraphicEqualizer eq;
    EXPECT_EQ(eq.GetPresetName(), "Flat");
    EXPECT_EQ(eq.GetBandsCount(), 10u);
    EXPECT_TRUE(eq.IsActive());
    EXPECT_DOUBLE_EQ(eq.GetPreampGainDb(), 0.0);
}

TEST(GraphicEqualizerTest, ApplyPresets) {
    GraphicEqualizer eq;
    eq.ApplyPreset("Rock");
    EXPECT_EQ(eq.GetPresetName(), "Rock");
    EXPECT_GT(eq.GetBand(0).GetGainDb(), 0.0);

    eq.ApplyPreset("Pop");
    EXPECT_EQ(eq.GetPresetName(), "Pop");

    eq.ResetAllBands();
    EXPECT_EQ(eq.GetPresetName(), "Flat");
    EXPECT_DOUBLE_EQ(eq.GetBand(0).GetGainDb(), 0.0);
}

TEST(GraphicEqualizerTest, BandAccessAndExceptions) {
    GraphicEqualizer eq;
    EXPECT_NO_THROW(eq.SetBandGain(2, 4.0));
    EXPECT_DOUBLE_EQ(eq.GetBand(2).GetGainDb(), 4.0);
    EXPECT_EQ(eq.GetPresetName(), "Custom");

    EXPECT_THROW(eq.SetBandGain(50, 1.0), InvalidEqualizerBandException);
    EXPECT_THROW(eq.GetBand(50), InvalidEqualizerBandException);

    eq.ToggleEqualizer(false);
    EXPECT_FALSE(eq.IsActive());
}

TEST(GraphicEqualizerTest, EqualityAndStream) {
    GraphicEqualizer e1;
    GraphicEqualizer e2;
    GraphicEqualizer e3("Rock");
    e3.ApplyPreset("Rock");

    EXPECT_EQ(e1, e2);
    EXPECT_NE(e1, e3);

    std::ostringstream oss;
    oss << e1;
    EXPECT_FALSE(oss.str().empty());
}