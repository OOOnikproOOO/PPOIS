/**
 * @file test_audio_effects_rack.cpp
 * @brief Unit tests for AudioEffectsRack class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioEffectsRack.h"

TEST(AudioEffectsRackTest, ConstructorAndGetters) {
    AudioEffectsRack rack;
    EXPECT_FALSE(rack.IsBypass());
    EXPECT_TRUE(rack.GetEqualizer().IsActive());
    EXPECT_FALSE(rack.GetReverb().IsActive());
    EXPECT_FALSE(rack.GetBassBoost().IsActive());
    EXPECT_FALSE(rack.GetPitch().IsActive());
}

TEST(AudioEffectsRackTest, BypassAndActiveEffects) {
    AudioEffectsRack rack;
    EXPECT_TRUE(rack.HasActiveEffects());

    rack.SetBypassAll(true);
    EXPECT_TRUE(rack.IsBypass());
    EXPECT_FALSE(rack.HasActiveEffects());

    rack.SetBypassAll(false);
    EXPECT_TRUE(rack.HasActiveEffects());
}

TEST(AudioEffectsRackTest, ResetAllEffects) {
    AudioEffectsRack rack;
    rack.GetReverb().ToggleEffect(true);
    rack.GetBassBoost().ToggleEffect(true);
    rack.GetPitch().SetPitchOffset(4);
    EXPECT_TRUE(rack.HasActiveEffects());

    rack.ResetAllEffects();
    EXPECT_FALSE(rack.GetReverb().IsActive());
    EXPECT_FALSE(rack.GetBassBoost().IsActive());
    EXPECT_FALSE(rack.GetPitch().IsActive());
    EXPECT_FALSE(rack.IsBypass());
}

TEST(AudioEffectsRackTest, EqualityAndStream) {
    AudioEffectsRack r1;
    AudioEffectsRack r2;
    AudioEffectsRack r3(true);

    EXPECT_EQ(r1, r2);
    EXPECT_NE(r1, r3);

    std::ostringstream oss;
    oss << r1;
    EXPECT_FALSE(oss.str().empty());
}