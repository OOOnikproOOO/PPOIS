/**
 * @file test_sound_card.cpp
 * @brief Unit tests for the SoundCard class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "SoundCard.h"
#include "Exceptions.h"

TEST(SoundCardTest, ConstructorAndGetters) {
    SoundCard card("Sound BlasterX", 6);
    EXPECT_EQ(card.GetCardModel(), "Sound BlasterX");
    EXPECT_EQ(card.GetChannelCount(), 6);
    EXPECT_EQ(card.GetJackCount(), 0);
}

TEST(SoundCardTest, AddJackAndAccess) {
    SoundCard card("Realtek Audio", 2);
    card.AddJack(AudioJack("Line Out", "Green", 32.0));
    card.AddJack(AudioJack("Mic In", "Pink", 1000.0));
    EXPECT_EQ(card.GetJackCount(), 2);

    EXPECT_EQ(card.GetJack(0).GetPortType(), "Line Out");
    EXPECT_THROW(card.GetJack(5), DeviceNotFoundException);
}

TEST(SoundCardTest, PlayAudioStreamAndSurround) {
    SoundCard card("ASUS Xonar", 2);
    card.PlayAudioStream(48000, 0.8);

    card.ConfigureSurround(6);
    EXPECT_EQ(card.GetChannelCount(), 6);

    card.PlayAudioStream(0, 0.5);

    EXPECT_THROW(card.PlayAudioStream(48000, 1.5), ComputerException);
    EXPECT_THROW(card.ConfigureSurround(4), ComputerException);
}

TEST(SoundCardTest, EqualityAndStream) {
    SoundCard c1("Model A", 2);
    SoundCard c2("Model A", 2);
    SoundCard c3("Model B", 6);

    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c1 != c3);

    std::stringstream ss;
    ss << c1;
    EXPECT_NE(ss.str().find("SoundCard:"), std::string::npos);
}