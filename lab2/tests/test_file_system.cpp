#include <gtest/gtest.h>
#include <sstream>
#include "FileSystem.h"
#include "DeviceNotFoundException.h"
#include "StorageOutOfSpaceException.h"

TEST(FileSystemTest, CreateReadWriteDeleteFilesAndDirectories) {
    FileSystem fs("ext4", 100);
    EXPECT_EQ(fs.GetFsType(), "ext4");
    EXPECT_EQ(fs.GetTotalCapacityBytes(), 100);
    EXPECT_EQ(fs.GetUsedSpaceBytes(), 0);
    EXPECT_EQ(fs.GetFreeSpaceBytes(), 100);

    fs.CreateDirectory("/", "docs");
    fs.CreateDirectory("/docs", "notes");
    fs.CreateFile("/docs/notes", "todo.txt", "Buy RAM");
    EXPECT_EQ(fs.ReadFile("/docs/notes", "todo.txt"), "Buy RAM");
    EXPECT_EQ(fs.GetUsedSpaceBytes(), 7);
    EXPECT_EQ(fs.GetFreeSpaceBytes(), 93);

    fs.WriteFile("/docs/notes", "todo.txt", "Buy DDR5 RAM!");
    EXPECT_EQ(fs.ReadFile("/docs/notes", "todo.txt"), "Buy DDR5 RAM!");
    EXPECT_EQ(fs.GetUsedSpaceBytes(), 13);

    fs.DeleteFile("/docs/notes", "todo.txt");
    EXPECT_EQ(fs.GetUsedSpaceBytes(), 0);
    EXPECT_THROW(fs.ReadFile("/docs/notes", "todo.txt"), DeviceNotFoundException);

    fs.DeleteDirectory("/docs", "notes");
    EXPECT_THROW(fs.NavigateToDirectory("/docs/notes"), DeviceNotFoundException);
}

TEST(FileSystemTest, StorageOutOfSpaceException) {
    FileSystem fs("NTFS", 10);
    EXPECT_THROW(fs.CreateFile("/", "big.txt", "0123456789ABCDEF"), StorageOutOfSpaceException);

    fs.CreateFile("/", "small.txt", "12345");
    EXPECT_THROW(fs.WriteFile("/", "small.txt", "01234567890"), StorageOutOfSpaceException);
}

TEST(FileSystemTest, EqualityAndStream) {
    FileSystem fs1("ext4", 512);
    FileSystem fs2("ext4", 512);
    FileSystem fs3("NTFS", 1024);

    fs1.CreateFile("/", "a.txt", "hi");
    fs2.CreateFile("/", "a.txt", "hi");

    EXPECT_TRUE(fs1 == fs2);
    EXPECT_FALSE(fs1 == fs3);
    EXPECT_TRUE(fs1 != fs3);

    std::ostringstream oss;
    oss << fs1;
    EXPECT_NE(oss.str().find("ext4"), std::string::npos);
}