#include <gtest/gtest.h>
#include <sstream>
#include "FileEntry.h"
#include "ComputerException.h"

TEST(FileEntryTest, ConstructorAndGetters) {
    FileEntry file("notes.txt", "Hello", false);
    EXPECT_EQ(file.GetName(), "notes.txt");
    EXPECT_EQ(file.ReadContent(), "Hello");
    EXPECT_EQ(file.GetSizeBytes(), 5);
    EXPECT_FALSE(file.IsReadOnly());
}

TEST(FileEntryTest, WriteAppendAndReadOnlyProtection) {
    FileEntry file("log.txt", "Init");
    file.AppendContent(" Done");
    EXPECT_EQ(file.ReadContent(), "Init Done");
    EXPECT_EQ(file.GetSizeBytes(), 9);

    file.WriteContent("Reset");
    EXPECT_EQ(file.ReadContent(), "Reset");
    EXPECT_EQ(file.GetSizeBytes(), 5);

    file.SetReadOnly(true);
    EXPECT_TRUE(file.IsReadOnly());
    EXPECT_THROW(file.WriteContent("Fail"), ComputerException);
    EXPECT_THROW(file.AppendContent("Fail"), ComputerException);
}

TEST(FileEntryTest, EqualityAndStream) {
    FileEntry f1("a.txt", "abc", false);
    FileEntry f2("a.txt", "abc", false);
    FileEntry f3("b.txt", "xyz", true);

    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
    EXPECT_TRUE(f1 != f3);

    std::ostringstream oss;
    oss << f1;
    EXPECT_NE(oss.str().find("a.txt"), std::string::npos);
}