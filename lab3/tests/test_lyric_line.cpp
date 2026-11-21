/**
 * @file test_lyric_line.cpp
 * @brief Unit tests for LyricLine class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "LyricLine.h"

TEST(LyricLineTest, ConstructorAndGetters) {
    LyricLine line(75.5, "Yesterday, all my troubles seemed so far away", false);
    EXPECT_DOUBLE_EQ(line.GetTimestampSec(), 75.5);
    EXPECT_EQ(line.GetText(), "Yesterday, all my troubles seemed so far away");
    EXPECT_FALSE(line.IsChorus());
}

TEST(LyricLineTest, ActiveAtAndAdjustment) {
    LyricLine line(10.0, "Refrain Line", true);
    EXPECT_TRUE(line.IsChorus());

    EXPECT_FALSE(line.IsActiveAt(9.9));
    EXPECT_TRUE(line.IsActiveAt(10.0));
    EXPECT_TRUE(line.IsActiveAt(13.5, 4.0));
    EXPECT_FALSE(line.IsActiveAt(15.0, 4.0));

    line.AdjustTimestamp(2.5);
    EXPECT_DOUBLE_EQ(line.GetTimestampSec(), 12.5);

    line.AdjustTimestamp(-50.0);
    EXPECT_DOUBLE_EQ(line.GetTimestampSec(), 0.0);
}

TEST(LyricLineTest, FormatAndSetText) {
    LyricLine line(65.25, "Hello World", false);
    std::string formatted = line.FormatTimestampedLine();
    EXPECT_NE(formatted.find("01:05.25"), std::string::npos);
    EXPECT_NE(formatted.find("Hello World"), std::string::npos);

    line.SetText("Updated World");
    EXPECT_EQ(line.GetText(), "Updated World");
}

TEST(LyricLineTest, EqualityAndStream) {
    LyricLine l1(15.0, "Line", false);
    LyricLine l2(15.0, "Line", false);
    LyricLine l3(15.0, "Other", false);

    EXPECT_EQ(l1, l2);
    EXPECT_NE(l1, l3);

    std::ostringstream oss;
    oss << l1;
    EXPECT_FALSE(oss.str().empty());
}