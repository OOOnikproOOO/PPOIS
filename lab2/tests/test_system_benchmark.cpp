#include <gtest/gtest.h>
#include <sstream>
#include "SystemBenchmark.h"

TEST(SystemBenchmarkTest, ConstructorAndGetters) {
    SystemBenchmark bench(1000, 2000, 500, 300);
    EXPECT_EQ(bench.GetCpuScore(), 1000);
    EXPECT_EQ(bench.GetGpuScore(), 2000);
    EXPECT_EQ(bench.GetMemoryScore(), 500);
    EXPECT_EQ(bench.GetStorageScore(), 300);
    EXPECT_EQ(bench.GetTotalScore(), 3800);
}

TEST(SystemBenchmarkTest, ExecuteBenchmarkSuites) {
    SystemBenchmark bench;
    bench.BenchmarkCpu(8, 4200);
    EXPECT_GT(bench.GetCpuScore(), 5000);

    bench.BenchmarkGpu(2200, 16384);
    EXPECT_GT(bench.GetGpuScore(), 10000);

    bench.BenchmarkMemory(32768, 3200);
    EXPECT_GT(bench.GetMemoryScore(), 5000);

    bench.BenchmarkStorage(2000, true);
    EXPECT_GT(bench.GetStorageScore(), 4000);

    EXPECT_GT(bench.GetTotalScore(), 20000);
}

TEST(SystemBenchmarkTest, EqualityAndStream) {
    SystemBenchmark b1(10, 20, 30, 40);
    SystemBenchmark b2(10, 20, 30, 40);
    SystemBenchmark b3(100, 200, 300, 400);

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
    EXPECT_TRUE(b1 != b3);

    std::ostringstream oss;
    oss << b1;
    EXPECT_NE(oss.str().find("100 pts"), std::string::npos);
}