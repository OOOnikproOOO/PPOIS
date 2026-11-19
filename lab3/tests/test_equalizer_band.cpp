/**
 * @file test_equalizer_band.cpp
 * @brief Unit tests for EqualizerBand class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "EqualizerBand.h"
#include "InvalidEqualizerBandException.h"

TEST(EqualizerBandTest, ConstructorAndGetters) {
    EqualizerBand band(250, 3.5, 1.8, true);
    EXPECT_EQ(band.GetCenterFrequencyHz(), 250);
    EXPECT_DOUBLE_EQ(band.GetGainDb(), 3.5);
    EXPECT_DOUBLE_EQ(band.GetQFactor(), 1.8);
    EXPECT_TRUE(band.IsEnabled());
}

TEST(EqualizerBandTest, GainAdjustmentAndExceptions) {
    EqualizerBand band(1000);
    EXPECT_NO_THROW(band.SetGain(6.0));
    EXPECT_DOUBLE_EQ(band.GetGainDb(), 6.0);

    EXPECT_THROW(band.SetGain(15.0), InvalidEqualizerBandException);
    EXPECT_THROW(band.SetGain(-15.0), InvalidEqualizerBandException);

    band.Reset();
    EXPECT_DOUBLE_EQ(band.GetGainDb(), 0.0);
}

TEST(EqualizerBandTest, QFactorAndToggle) {
    EqualizerBand band;
    band.SetQFactor(3.0);
    EXPECT_DOUBLE_EQ(band.GetQFactor(), 3.0);

    band.SetQFactor(50.0);
    EXPECT_DOUBLE_EQ(band.GetQFactor(), 3.0);

    band.ToggleBand(false);
    EXPECT_FALSE(band.IsEnabled());
}

TEST(EqualizerBandTest, EqualityAndStream) {
    EqualizerBand b1(500, 2.0);
    EqualizerBand b2(500, 2.0);
    EqualizerBand b3(1000, 2.0);

    EXPECT_EQ(b1, b2);
    EXPECT_NE(b1, b3);

    std::ostringstream oss;
    oss << b1;
    EXPECT_FALSE(oss.str().empty());
}