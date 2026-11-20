/**
 * @file test_music_player.cpp
 * @brief Unit tests for MusicPlayer class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "MusicPlayer.h"

TEST(MusicPlayerTest, ConstructorAndGetters) {
    MusicPlayer player("CyberPlayer 2077");
    EXPECT_EQ(player.GetPlayerName(), "CyberPlayer 2077");
    EXPECT_TRUE(player.IsPoweredOn());
    EXPECT_EQ(player.GetQueue().GetQueueSize(), 0u);
    EXPECT_EQ(player.GetEngine().GetState(), "Stopped");
}

TEST(MusicPlayerTest, PowerControlAndLoadTrack) {
    MusicPlayer player;
    AudioTrack track("music/rock.mp3", 240.0, AudioMetadata("Bohemian Rhapsody", "Queen"));

    player.LoadAndQueueTrack(track);
    EXPECT_EQ(player.GetQueue().GetQueueSize(), 1u);

    EXPECT_TRUE(player.Play());
    EXPECT_EQ(player.GetEngine().GetState(), "Playing");
    EXPECT_EQ(player.GetHistory().GetEntriesCount(), 1u);

    player.Pause();
    EXPECT_EQ(player.GetEngine().GetState(), "Paused");

    player.Stop();
    EXPECT_EQ(player.GetEngine().GetState(), "Stopped");

    player.PowerOff();
    EXPECT_FALSE(player.IsPoweredOn());
    EXPECT_FALSE(player.Play());

    player.PowerOn();
    EXPECT_TRUE(player.IsPoweredOn());
}

TEST(MusicPlayerTest, NavigationAndSeek) {
    MusicPlayer player;
    AudioTrack t1("m/1.mp3", 180.0, AudioMetadata("Track 1"));
    AudioTrack t2("m/2.mp3", 200.0, AudioMetadata("Track 2"));

    player.LoadAndQueueTrack(t1);
    player.LoadAndQueueTrack(t2);

    player.Play();
    player.Seek(60.0);
    EXPECT_DOUBLE_EQ(player.GetPosition().GetCurrentSec(), 60.0);

    EXPECT_TRUE(player.Next());
    EXPECT_EQ(player.GetQueue().GetCurrentIndex(), 1);

    EXPECT_TRUE(player.Previous());
    EXPECT_EQ(player.GetQueue().GetCurrentIndex(), 0);

    std::string summary = player.GetStatusSummary();
    EXPECT_NE(summary.find("POWER ON"), std::string::npos);
}

TEST(MusicPlayerTest, SubsystemReferences) {
    MusicPlayer player;
    player.GetVolume().SetVolume(85);
    EXPECT_EQ(player.GetVolume().GetVolumeLevel(), 85);

    player.GetRepeat().SetMode("RepeatAll");
    EXPECT_EQ(player.GetRepeat().GetMode(), "RepeatAll");

    player.GetEffectsRack().GetEqualizer().ApplyPreset("Rock");
    EXPECT_EQ(player.GetEffectsRack().GetEqualizer().GetPresetName(), "Rock");
}

TEST(MusicPlayerTest, EqualityAndStream) {
    MusicPlayer p1("Player");
    MusicPlayer p2("Player");
    MusicPlayer p3("Other");

    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_FALSE(oss.str().empty());
}