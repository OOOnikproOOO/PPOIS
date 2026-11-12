#include <gtest/gtest.h>
#include <sstream>
#include "OSProcess.h"
#include "MemoryAllocationException.h"

TEST(OSProcessTest, ConstructorAndGetters) {
    OSProcess proc(42, "clangd", 256, true);
    EXPECT_EQ(proc.GetPid(), 42);
    EXPECT_EQ(proc.GetProcessName(), "clangd");
    EXPECT_EQ(proc.GetMemoryMb(), 256);
    EXPECT_TRUE(proc.IsRunning());
}

TEST(OSProcessTest, SuspendResumeAndMemoryOperations) {
    OSProcess proc(10, "chrome", 512, true);
    proc.Suspend();
    EXPECT_FALSE(proc.IsRunning());
    proc.Resume();
    EXPECT_TRUE(proc.IsRunning());

    proc.AllocateMemory(128);
    EXPECT_EQ(proc.GetMemoryMb(), 640);
    EXPECT_THROW(proc.AllocateMemory(0), MemoryAllocationException);

    proc.FreeMemory(200);
    EXPECT_EQ(proc.GetMemoryMb(), 440);
    proc.FreeMemory(1000);
    EXPECT_EQ(proc.GetMemoryMb(), 0);
}

TEST(OSProcessTest, EqualityAndStream) {
    OSProcess p1(1, "init", 32, true);
    OSProcess p2(1, "init", 32, true);
    OSProcess p3(2, "bash", 16, false);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);

    std::ostringstream oss;
    oss << p1;
    EXPECT_NE(oss.str().find("init"), std::string::npos);
}