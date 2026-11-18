/**
 * @file test_music_library.cpp
 * @brief Unit tests for MusicLibrary class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "MusicLibrary.h"
#include "TrackNotFoundException.h"
#include "PlaylistNotFoundException.h"

TEST(MusicLibraryTest, ConstructorAndGetters) {
    MusicLibrary lib("Personal Music Base");
    EXPECT_EQ(lib.GetLibraryName(), "Personal Music Base");
    EXPECT_EQ(lib.GetTracks().size(), 0u);
    EXPECT_EQ(lib.GetAlbums().size(), 0u);
    EXPECT_EQ(lib.GetPlaylists().size(), 0u);
}

TEST(MusicLibraryTest, AddAndFindTracks) {
    MusicLibrary lib;
    AudioTrack t1("song1.mp3", 150.0, AudioMetadata("Track 1"));
    AudioTrack t2("song2.mp3", 200.0, AudioMetadata("Track 2"));

    t1.Play();
    t1.Play();
    lib.AddTrack(t1);
    lib.AddTrack(t2);

    EXPECT_EQ(lib.GetTracks().size(), 2u);
    EXPECT_DOUBLE_EQ(lib.GetTotalListeningTimeSec(), 300.0);

    const AudioTrack& found = lib.FindTrackByTitle("Track 1");
    EXPECT_EQ(found.GetMetadata().GetTitle(), "Track 1");

    EXPECT_THROW(lib.FindTrackByTitle("Nonexistent"), TrackNotFoundException);
}

TEST(MusicLibraryTest, AddAndFindPlaylists) {
    MusicLibrary lib;
    Playlist p1("Rock Classics");
    Playlist p2("Chillout");

    lib.AddPlaylist(p1);
    lib.AddPlaylist(p2);

    EXPECT_EQ(lib.GetPlaylists().size(), 2u);
    const Playlist& found = lib.FindPlaylistByName("Chillout");
    EXPECT_EQ(found.GetName(), "Chillout");

    EXPECT_THROW(lib.FindPlaylistByName("Pop"), PlaylistNotFoundException);
}

TEST(MusicLibraryTest, EqualityAndStream) {
    MusicLibrary l1("Base");
    MusicLibrary l2("Base");
    MusicLibrary l3("Other");

    EXPECT_EQ(l1, l2);
    EXPECT_NE(l1, l3);

    std::ostringstream oss;
    oss << l1;
    EXPECT_FALSE(oss.str().empty());
}