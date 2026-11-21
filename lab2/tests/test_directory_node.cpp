#include <gtest/gtest.h>
#include <sstream>
#include "DirectoryNode.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

TEST(DirectoryNodeTest, AddRemoveFilesAndSubdirs) {
    DirectoryNode root("root");
    root.AddFile(FileEntry("readme.txt", "hello"));
    EXPECT_EQ(root.GetFileCount(), 1);
    EXPECT_EQ(root.GetFile(0).GetName(), "readme.txt");
    EXPECT_EQ(root.GetFileByName("readme.txt").ReadContent(), "hello");

    EXPECT_THROW(root.AddFile(FileEntry("")), ComputerException);
    EXPECT_THROW(root.AddFile(FileEntry("readme.txt", "dup")), ComputerException);
    EXPECT_THROW(root.GetFile(5), DeviceNotFoundException);
    EXPECT_THROW(root.GetFileByName("missing.txt"), DeviceNotFoundException);

    DirectoryNode docs("docs");
    docs.AddFile(FileEntry("lab.txt", "1234567890"));
    root.AddSubdirectory(docs);

    EXPECT_EQ(root.GetSubdirectoryCount(), 1);
    EXPECT_EQ(root.CalculateTotalSizeBytes(), 15);
    EXPECT_EQ(root.CountTotalFiles(), 2);
    EXPECT_EQ(root.GetSubdirectory(0).GetName(), "docs");
    EXPECT_EQ(root.GetSubdirectoryByName("docs").GetFileCount(), 1);

    EXPECT_THROW(root.AddSubdirectory(DirectoryNode("")), ComputerException);
    EXPECT_THROW(root.AddSubdirectory(DirectoryNode("docs")), ComputerException);
    EXPECT_THROW(root.GetSubdirectory(2), DeviceNotFoundException);
    EXPECT_THROW(root.GetSubdirectoryByName("other"), DeviceNotFoundException);

    root.RemoveFile("readme.txt");
    EXPECT_EQ(root.GetFileCount(), 0);
    EXPECT_THROW(root.RemoveFile("readme.txt"), DeviceNotFoundException);

    root.RemoveSubdirectory("docs");
    EXPECT_EQ(root.GetSubdirectoryCount(), 0);
    EXPECT_THROW(root.RemoveSubdirectory("docs"), DeviceNotFoundException);
}

TEST(DirectoryNodeTest, EqualityAndStream) {
    DirectoryNode d1("home");
    DirectoryNode d2("home");
    DirectoryNode d3("var");
    d1.AddFile(FileEntry("f.txt", "123"));
    d2.AddFile(FileEntry("f.txt", "123"));

    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_TRUE(d1 != d3);

    std::ostringstream oss;
    oss << d1;
    EXPECT_NE(oss.str().find("home"), std::string::npos);
}