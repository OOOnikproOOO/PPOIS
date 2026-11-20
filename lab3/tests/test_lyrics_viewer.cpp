/**
 * @file test_lyrics_viewer.cpp
 * @brief Unit tests for LyricsViewer class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "LyricsViewer.h"

TEST(LyricsViewerTest, ConstructorAndGetters) {
    LyricsViewer viewer(true, 18);
    EXPECT_TRUE(viewer.IsKaraokeMode());
    EXPECT_EQ(viewer.GetFontSize(), 18);
    EXPECT_EQ(viewer.GetLinesCount(), 0u);
}

TEST(LyricsViewerTest, AddLineAndFindCurrent) {
    LyricsViewer viewer;
    viewer.AddLine(LyricLine(5.0, "Line 1"));
    viewer.AddLine(LyricLine(12.0, "Line 2"));
    viewer.AddLine(LyricLine(20.0, "Line 3"));

    EXPECT_EQ(viewer.GetLinesCount(), 3u);

    EXPECT_EQ(viewer.GetCurrentLine(4.0), nullptr);

    const LyricLine* current = viewer.GetCurrentLine(5.5);
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->GetText(), "Line 1");

    current = viewer.GetCurrentLine(15.0);
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->GetText(), "Line 2");

    current = viewer.GetCurrentLine(100.0);
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->GetText(), "Line 3");
}

TEST(LyricsViewerTest, FontSizeAndModes) {
    LyricsViewer viewer;
    viewer.SetKaraokeMode(false);
    EXPECT_FALSE(viewer.IsKaraokeMode());

    viewer.SetFontSize(5);
    EXPECT_EQ(viewer.GetFontSize(), 8);

    viewer.SetFontSize(100);
    EXPECT_EQ(viewer.GetFontSize(), 48);

    viewer.AddLine(LyricLine(1.0, "Some line"));
    viewer.Clear();
    EXPECT_EQ(viewer.GetLinesCount(), 0u);
}

TEST(LyricsViewerTest, EqualityAndStream) {
    LyricsViewer v1(true, 14);
    LyricsViewer v2(true, 14);
    LyricsViewer v3(false, 14);

    EXPECT_EQ(v1, v2);
    EXPECT_NE(v1, v3);

    std::ostringstream oss;
    oss << v1;
    EXPECT_FALSE(oss.str().empty());
}