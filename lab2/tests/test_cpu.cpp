/**
 * @file test_cpu.cpp
 * @brief Unit tests for the CPU class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "CPU.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

TEST(CPUTest, ConstructorAndDefaultState) {
    CPU cpu("AMD Ryzen 7 7800X3D", "AM5", 120, 98304);
    EXPECT_EQ(cpu.GetModelName(), "AMD Ryzen 7 7800X3D");
    EXPECT_EQ(cpu.GetSocketType(), "AM5");
    EXPECT_EQ(cpu.GetTdpWatts(), 120);
    EXPECT_EQ(cpu.GetCoreCount(), 0);
    EXPECT_FALSE(cpu.IsOverclocked());
    EXPECT_DOUBLE_EQ(cpu.GetAverageTemperature(), 25.0);
    EXPECT_EQ(cpu.CalculateCurrentPowerDraw(), 10);
}

TEST(CPUTest, AddCoresAndComputeWorkload) {
    CPU cpu("Intel Core i5-13600K", "LGA1700", 125, 24576);
    cpu.AddCore(CPUCore(0, 3500));
    cpu.AddCore(CPUCore(1, 3500));
    EXPECT_EQ(cpu.GetCoreCount(), 2);

    cpu.ComputeWorkload(2000000LL);
    EXPECT_GT(cpu.GetAverageTemperature(), 35.0);
    EXPECT_GT(cpu.CalculateCurrentPowerDraw(), 25);
}

TEST(CPUTest, EmptyCoresWorkloadException) {
    CPU cpu;
    EXPECT_THROW(cpu.ComputeWorkload(1000LL), DeviceNotFoundException);
}

TEST(CPUTest, OverclockSuccessAndFailures) {
    CPU cpu("Ryzen 5 7600", "AM5", 65, 32768);
    cpu.AddCore(CPUCore(0, 3800));

    EXPECT_THROW(cpu.Overclock(0.9), ComputerException);
    EXPECT_THROW(cpu.Overclock(2.5), ComputerException);

    cpu.Overclock(1.2);
    EXPECT_TRUE(cpu.IsOverclocked());
}

TEST(CPUTest, EqualityAndStreamOutput) {
    CPU c1("Ryzen 7", "AM5", 105);
    CPU c2("Ryzen 7", "AM5", 105);
    CPU c3("Core i7", "LGA1700", 125);

    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c1 != c3);

    std::stringstream ss;
    ss << c1;
    EXPECT_NE(ss.str().find("Ryzen 7"), std::string::npos);
}

TEST(CPUTest, CoolDownAndCoreAccess) {
    CPU cpu("AMD Ryzen 9", "AM5", 170, 65536);
    cpu.AddCore(CPUCore(0, 4000));
    cpu.ComputeWorkload(5000000LL);
    double temp_before = cpu.GetAverageTemperature();

    cpu.CoolDown(10.0);
    EXPECT_LT(cpu.GetAverageTemperature(), temp_before);

    EXPECT_EQ(cpu.GetCore(0).GetCoreId(), 0);
    EXPECT_THROW(cpu.GetCore(5), DeviceNotFoundException);
    EXPECT_EQ(cpu.GetL3Cache().GetSizeKb(), 65536);
}