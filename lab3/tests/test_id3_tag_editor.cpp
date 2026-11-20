/**
 * @file test_id3_tag_editor.cpp
 * @brief Unit tests for ID3TagEditor class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "ID3TagEditor.h"

TEST(ID3TagEditorTest, ConstructorAndGetters) {
    ID3TagEditor editor(4, "UTF-8", "Remastered");
    EXPECT_EQ(editor.GetTagVersion(), 4);
    EXPECT_EQ(editor.GetEncoding(), "UTF-8");
    EXPECT_EQ(editor.GetComment(), "Remastered");
    EXPECT_FALSE(editor.IsDirty());
}

TEST(ID3TagEditorTest, ApplyTagsAndDirtyFlag) {
    ID3TagEditor editor;
    AudioTrack track;

    editor.ApplyTags(track, "New Title", "New Artist", "New Album", "Jazz", 2025, 3);
    EXPECT_TRUE(editor.IsDirty());
    EXPECT_EQ(track.GetMetadata().GetTitle(), "New Title");
    EXPECT_EQ(track.GetMetadata().GetArtist(), "New Artist");

    editor.SaveChanges();
    EXPECT_FALSE(editor.IsDirty());

    editor.SetComment("Live Version");
    EXPECT_TRUE(editor.IsDirty());
    EXPECT_EQ(editor.GetComment(), "Live Version");

    editor.RevertChanges();
    EXPECT_FALSE(editor.IsDirty());
}

TEST(ID3TagEditorTest, EqualityAndStream) {
    ID3TagEditor e1(3, "UTF-8");
    ID3TagEditor e2(3, "UTF-8");
    ID3TagEditor e3(4, "UTF-8");

    EXPECT_EQ(e1, e2);
    EXPECT_NE(e1, e3);

    std::ostringstream oss;
    oss << e1;
    EXPECT_FALSE(oss.str().empty());
}