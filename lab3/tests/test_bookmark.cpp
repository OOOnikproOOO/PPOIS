/**
 * @file test_bookmark.cpp
 * @brief Unit tests for Bookmark class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Bookmark.h"

TEST(BookmarkTest, ConstructorAndGetters) {
    Bookmark bm("Podcast Episode 1", 154.0, "Great interview part", "2026.11.19");
    EXPECT_EQ(bm.GetTrackTitle(), "Podcast Episode 1");
    EXPECT_DOUBLE_EQ(bm.GetTimestampSec(), 154.0);
    EXPECT_EQ(bm.GetNote(), "Great interview part");
    EXPECT_EQ(bm.GetCreationDate(), "2026.11.19");
}

TEST(BookmarkTest, FormatAndModification) {
    Bookmark bm("Song", 125.0, "Solo");
    EXPECT_EQ(bm.FormatBookmarkString(), "Song @ 02:05 (Solo)");

    bm.UpdateNote("Epic guitar solo");
    EXPECT_EQ(bm.GetNote(), "Epic guitar solo");

    bm.AdjustTimestamp(10.0);
    EXPECT_DOUBLE_EQ(bm.GetTimestampSec(), 135.0);

    bm.AdjustTimestamp(-200.0);
    EXPECT_DOUBLE_EQ(bm.GetTimestampSec(), 0.0);
}

TEST(BookmarkTest, EqualityAndStream) {
    Bookmark b1("Track", 50.0);
    Bookmark b2("Track", 50.0);
    Bookmark b3("Other", 50.0);

    EXPECT_EQ(b1, b2);
    EXPECT_NE(b1, b3);

    std::ostringstream oss;
    oss << b1;
    EXPECT_FALSE(oss.str().empty());
}