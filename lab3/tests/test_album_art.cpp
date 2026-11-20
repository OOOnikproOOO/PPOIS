/**
 * @file test_album_art.cpp
 * @brief Unit tests for AlbumArt class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "AlbumArt.h"

TEST(AlbumArtTest, ConstructorAndGetters) {
    AlbumArt art(".png", 800, 600, 204800);
    EXPECT_EQ(art.GetMimeType(), ".png");
    EXPECT_EQ(art.GetWidth(), 800);
    EXPECT_EQ(art.GetHeight(), 600);
    EXPECT_EQ(art.GetDataSizeBytes(), 204800u);
    EXPECT_TRUE(art.IsValid());
}

TEST(AlbumArtTest, AspectRatioAndFormatting) {
    AlbumArt art(".jpeg", 1920, 1080, 500000);
    EXPECT_NEAR(art.GetAspectRatio(), 16.0 / 9.0, 0.01);

    std::string dims = art.FormatDimensions();
    EXPECT_NE(dims.find("1920x1080"), std::string::npos);
    EXPECT_NE(dims.find(".jpeg"), std::string::npos);

    art.Clear();
    EXPECT_FALSE(art.IsValid());
    EXPECT_DOUBLE_EQ(art.GetAspectRatio(), 0.0);
}

TEST(AlbumArtTest, EqualityAndStream) {
    AlbumArt a1(".png", 500, 500, 50000);
    AlbumArt a2(".png", 500, 500, 50000);
    AlbumArt a3(".jpeg", 500, 500, 50000);

    EXPECT_EQ(a1, a2);
    EXPECT_NE(a1, a3);

    std::ostringstream oss;
    oss << a1;
    EXPECT_FALSE(oss.str().empty());
}