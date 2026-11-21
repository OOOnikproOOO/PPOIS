/**
 * @file test_audio_track.cpp
 * @brief Unit tests for AudioTrack class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AudioTrack.h"

TEST(AudioTrackTest, ConstructorAndGetters) {
    AudioMetadata meta("Imagine", "John Lennon", "Imagine", "Rock", 1971, 1);
    AudioCodec codec("FLAC", 850, 44100, 2, true);
    AudioTrack track("music/imagine.flac", 183.0, meta, codec);

    EXPECT_EQ(track.GetFilePath(), "music/imagine.flac");
    EXPECT_DOUBLE_EQ(track.GetDurationSec(), 183.0);
    EXPECT_EQ(track.GetPlayCount(), 0);
    EXPECT_FALSE(track.IsFavorite());
    EXPECT_EQ(track.GetMetadata().GetTitle(), "Imagine");
    EXPECT_EQ(track.GetCodec().GetCodecName(), "FLAC");
    EXPECT_EQ(track.FormatDurationString(), "03:03");
}

TEST(AudioTrackTest, PlayAndFavorite) {
    AudioTrack track("song.mp3", 125.0);
    EXPECT_EQ(track.GetPlayCount(), 0);

    track.Play();
    track.Play();
    EXPECT_EQ(track.GetPlayCount(), 2);

    EXPECT_FALSE(track.IsFavorite());
    track.ToggleFavorite();
    EXPECT_TRUE(track.IsFavorite());
    track.ToggleFavorite();
    EXPECT_FALSE(track.IsFavorite());
}

TEST(AudioTrackTest, UpdateMetadata) {
    AudioTrack track("song.mp3", 120.0);
    AudioMetadata new_meta("New Song", "New Artist", "New Album", "Jazz", 2024, 2);
    track.UpdateMetadata(new_meta);
    EXPECT_EQ(track.GetMetadata().GetTitle(), "New Song");
    EXPECT_EQ(track.GetMetadata().GetArtist(), "New Artist");
}

TEST(AudioTrackTest, EqualityAndStream) {
    AudioTrack t1("song.mp3", 100.0);
    AudioTrack t2("song.mp3", 100.0);
    AudioTrack t3("other.mp3", 100.0);

    EXPECT_EQ(t1, t2);
    EXPECT_NE(t1, t3);

    std::ostringstream oss;
    oss << t1;
    EXPECT_FALSE(oss.str().empty());
}