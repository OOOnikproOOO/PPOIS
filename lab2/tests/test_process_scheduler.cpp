#include <gtest/gtest.h>
#include <sstream>
#include "ProcessScheduler.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"
#include "MemoryAllocationException.h"

TEST(ProcessSchedulerTest, LaunchTerminateAndMetrics) {
    ProcessScheduler sched("CFS", 2);
    EXPECT_EQ(sched.GetPolicy(), "CFS");
    EXPECT_EQ(sched.GetMaxProcesses(), 2);

    sched.LaunchProcess(OSProcess(1, "systemd", 64, true));
    sched.LaunchProcess(OSProcess(2, "dockerd", 256, false));
    EXPECT_EQ(sched.GetProcessCount(), 2);
    EXPECT_EQ(sched.CalculateTotalMemoryUsageMb(), 320);
    EXPECT_EQ(sched.CountRunningProcesses(), 1);
    EXPECT_EQ(sched.GetProcess(0).GetProcessName(), "systemd");

    EXPECT_THROW(sched.LaunchProcess(OSProcess(3, "vim", 32, true)), MemoryAllocationException);

    sched.TerminateProcess(2);
    EXPECT_EQ(sched.GetProcessCount(), 1);
    EXPECT_THROW(sched.LaunchProcess(OSProcess(1, "dup", 10, true)), ComputerException);
    EXPECT_THROW(sched.TerminateProcess(99), DeviceNotFoundException);
    EXPECT_THROW(sched.GetProcess(5), DeviceNotFoundException);
}

TEST(ProcessSchedulerTest, EqualityAndStream) {
    ProcessScheduler s1("CFS", 32);
    ProcessScheduler s2("CFS", 32);
    ProcessScheduler s3("RoundRobin", 16);

    s1.LaunchProcess(OSProcess(1, "kernel", 128, true));
    s2.LaunchProcess(OSProcess(1, "kernel", 128, true));

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_TRUE(s1 != s3);

    std::ostringstream oss;
    oss << s1;
    EXPECT_NE(oss.str().find("CFS"), std::string::npos);
}