/**
 * @file test_computer_case.cpp
 * @brief Unit tests for the ComputerCase class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "ComputerCase.h"
#include "Exceptions.h"

TEST(ComputerCaseTest, ConstructorAndGetters) {
    ComputerCase ccase("NZXT H510", "ATX", 381, 165, 10.0);
    EXPECT_EQ(ccase.GetModelName(), "NZXT H510");
    EXPECT_EQ(ccase.GetSupportedFormFactor(), "ATX");
    EXPECT_EQ(ccase.GetMaxGpuLengthMm(), 381);
    EXPECT_EQ(ccase.GetMaxCpuCoolerHeightMm(), 165);
    EXPECT_DOUBLE_EQ(ccase.GetDustFilterClogPercentage(), 10.0);
}

TEST(ComputerCaseTest, CheckMotherboardCompatibility) {
    ComputerCase atxCase("Fractal Meshify 2", "ATX", 450, 185);
    EXPECT_TRUE(atxCase.CheckMotherboardCompatibility("ATX"));
    EXPECT_TRUE(atxCase.CheckMotherboardCompatibility("Micro-ATX"));
    EXPECT_TRUE(atxCase.CheckMotherboardCompatibility("Mini-ITX"));
    EXPECT_FALSE(atxCase.CheckMotherboardCompatibility("E-ATX"));

    ComputerCase itxCase("Cooler Master NR200", "Mini-ITX", 330, 155);
    EXPECT_TRUE(itxCase.CheckMotherboardCompatibility("Mini-ITX"));
    EXPECT_FALSE(itxCase.CheckMotherboardCompatibility("ATX"));
}

TEST(ComputerCaseTest, CheckGpuFit) {
    ComputerCase ccase("Meshify 2", "ATX", 400, 185);
    EXPECT_TRUE(ccase.CheckGpuFit(304));
    EXPECT_TRUE(ccase.CheckGpuFit(400));
    EXPECT_FALSE(ccase.CheckGpuFit(420));
    EXPECT_FALSE(ccase.CheckGpuFit(-10));
}

TEST(ComputerCaseTest, AccumulateDustAndClean) {
    ComputerCase ccase("Meshify 2", "ATX", 400, 185, 0.0);
    ccase.AccumulateDust(30.0);
    EXPECT_DOUBLE_EQ(ccase.GetDustFilterClogPercentage(), 30.0);

    ccase.CleanFilters();
    EXPECT_DOUBLE_EQ(ccase.GetDustFilterClogPercentage(), 0.0);

    EXPECT_THROW(ccase.AccumulateDust(90.0), ThermalThrottlingException);
}

TEST(ComputerCaseTest, EqualityAndStream) {
    ComputerCase c1("Meshify 2", "ATX", 450, 185, 0.0);
    ComputerCase c2("Meshify 2", "ATX", 450, 185, 0.0);
    ComputerCase c3("H510", "ATX", 381, 165, 0.0);

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_TRUE(c1 != c3);

    std::ostringstream oss;
    oss << c1;
    EXPECT_FALSE(oss.str().empty());
}