/**
 * @file test_music_folder.cpp
 * @brief Unit tests for MusicFolder class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "MusicFolder.h"

TEST(MusicFolderTest, ConstructorAndGetters) {
    MusicFolder folder("D:/Audio/Lossless", true);
    EXPECT_EQ(folder.GetFolderPath(), "D:/Audio/Lossless");
    EXPECT_TRUE(folder.IsRecursive());
    EXPECT_EQ(folder.GetDiscoveredFiles().size(), 0u);
}

TEST(MusicFolderTest, AddExtensionAndScan) {
    MusicFolder folder("C:/Music", false);
    folder.AddAllowedExtension(".ogg");
    folder.AddAllowedExtension(".ogg");

    std::vector<std::string> disk_files = {
        "song1.mp3",
        "notes.txt",
        "audio.flac",
        "track.ogg",
        "image.png"
    };

    size_t found = folder.ScanFolder(disk_files);
    EXPECT_EQ(found, 3u);
    EXPECT_EQ(folder.GetDiscoveredFiles().size(), 3u);

    EXPECT_TRUE(folder.ContainsFile("C:/Music/song1.mp3"));
    EXPECT_TRUE(folder.ContainsFile("C:/Music/audio.flac"));
    EXPECT_TRUE(folder.ContainsFile("C:/Music/track.ogg"));
    EXPECT_FALSE(folder.ContainsFile("C:/Music/notes.txt"));

    folder.ClearScannedFiles();
    EXPECT_EQ(folder.GetDiscoveredFiles().size(), 0u);
}

TEST(MusicFolderTest, EqualityAndStream) {
    MusicFolder f1("C:/Music", true);
    MusicFolder f2("C:/Music", true);
    MusicFolder f3("D:/Music", true);

    EXPECT_EQ(f1, f2);
    EXPECT_NE(f1, f3);

    std::ostringstream oss;
    oss << f1;
    EXPECT_FALSE(oss.str().empty());
}