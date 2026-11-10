/**
 * @file test_audio_jack.cpp
 * @brief Unit tests for the AudioJack class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioJack.h"

TEST(AudioJackTest, ConstructorAndGetters) {
    AudioJack jack("Line Out 3.5mm", "Green", 32.0);
    EXPECT_EQ(jack.GetPortType(), "Line Out 3.5mm");
    EXPECT_EQ(jack.GetColorCode(), "Green");
    EXPECT_DOUBLE_EQ(jack.GetImpedanceOhms(), 32.0);
    EXPECT_FALSE(jack.IsPlugged());
}

TEST(AudioJackTest, PlugInAndUnplug) {
    AudioJack jack("Headphone Out", "Black", 16.0);
    EXPECT_FALSE(jack.IsPlugged());

    jack.PlugIn();
    EXPECT_TRUE(jack.IsPlugged());

    jack.Unplug();
    EXPECT_FALSE(jack.IsPlugged());
}

TEST(AudioJackTest, ImpedanceMatching) {
    AudioJack jack("Headphone Out", "Green", 32.0);
    EXPECT_TRUE(jack.VerifyImpedanceMatch(32.0));
    EXPECT_TRUE(jack.VerifyImpedanceMatch(250.0));
    EXPECT_FALSE(jack.VerifyImpedanceMatch(1.0));
    EXPECT_FALSE(jack.VerifyImpedanceMatch(1000.0));
}

TEST(AudioJackTest, EqualityAndStream) {
    AudioJack j1("Line Out", "Green", 32.0);
    AudioJack j2("Line Out", "Green", 32.0);
    AudioJack j3("Mic In", "Pink", 1000.0);

    EXPECT_TRUE(j1 == j2);
    EXPECT_TRUE(j1 != j3);

    std::stringstream ss;
    ss << j1;
    EXPECT_NE(ss.str().find("AudioJack"), std::string::npos);
}