/**
 * @file test_spectrum_analyzer.cpp
 * @brief Unit tests for SpectrumAnalyzer class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "SpectrumAnalyzer.h"

TEST(SpectrumAnalyzerTest, ConstructorAndGetters) {
    SpectrumAnalyzer analyzer(16, 0.05, true);
    EXPECT_EQ(analyzer.GetBandsCount(), 16u);
    EXPECT_DOUBLE_EQ(analyzer.GetPeakDecayRate(), 0.05);
    EXPECT_TRUE(analyzer.IsActive());
    EXPECT_DOUBLE_EQ(analyzer.CalculateTotalEnergy(), 0.0);
}

TEST(SpectrumAnalyzerTest, ProcessBufferAndEnergies) {
    SpectrumAnalyzer analyzer(8, 0.1, true);
    AudioBuffer buffer(100);

    for (int i = 0; i < 50; i++)
        buffer.WriteSample(AudioSample(0.5, 0.5, 16));

    analyzer.ProcessBuffer(buffer);
    EXPECT_GT(analyzer.CalculateTotalEnergy(), 0.0);
    EXPECT_GT(analyzer.GetBandEnergy(0), 0.0);
    EXPECT_DOUBLE_EQ(analyzer.GetBandEnergy(100), 0.0);

    analyzer.Reset();
    EXPECT_DOUBLE_EQ(analyzer.CalculateTotalEnergy(), 0.0);
}

TEST(SpectrumAnalyzerTest, DecayAndToggle) {
    SpectrumAnalyzer analyzer(8, 0.2, true);
    AudioBuffer buffer(10);
    buffer.WriteSample(AudioSample(1.0, 1.0, 16));

    analyzer.ProcessBuffer(buffer);
    double initial_energy = analyzer.CalculateTotalEnergy();

    AudioBuffer empty_buffer(10);
    analyzer.ProcessBuffer(empty_buffer);
    EXPECT_LT(analyzer.CalculateTotalEnergy(), initial_energy);

    analyzer.ToggleActive(false);
    EXPECT_FALSE(analyzer.IsActive());
}

TEST(SpectrumAnalyzerTest, EqualityAndStream) {
    SpectrumAnalyzer a1(10, 0.05);
    SpectrumAnalyzer a2(10, 0.05);
    SpectrumAnalyzer a3(16, 0.05);

    EXPECT_EQ(a1, a2);
    EXPECT_NE(a1, a3);

    std::ostringstream oss;
    oss << a1;
    EXPECT_FALSE(oss.str().empty());
}