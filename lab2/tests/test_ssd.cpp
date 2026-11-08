/**
 * @file test_ssd.cpp
 * @brief Unit tests for the SSD class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "SSD.h"
#include "Exceptions.h"

TEST(SSDTest, ConstructorAndGetters) {
    SSD ssd("Samsung 990 PRO", "NVMe PCIe 4.0", 2000, 1200.0);
    EXPECT_EQ(ssd.GetModel(), "Samsung 990 PRO");
    EXPECT_EQ(ssd.GetInterfaceType(), "NVMe PCIe 4.0");
    EXPECT_EQ(ssd.GetCapacityGb(), 2000);
    EXPECT_EQ(ssd.GetUsedGb(), 0);
    EXPECT_EQ(ssd.GetFreeSpaceGb(), 2000);
    EXPECT_DOUBLE_EQ(ssd.GetTbwResourceTb(), 1200.0);
    EXPECT_DOUBLE_EQ(ssd.GetTbwWrittenTb(), 0.0);
    EXPECT_EQ(ssd.GetHealthPercentage(), 100);
}

TEST(SSDTest, WriteAndReadOperations) {
    SSD ssd("Kingston KC3000", "NVMe PCIe 4.0", 1000, 800.0);
    EXPECT_FALSE(ssd.WriteData(0.0));
    EXPECT_TRUE(ssd.WriteData(100.0));
    EXPECT_EQ(ssd.GetUsedGb(), 100);
    EXPECT_GT(ssd.GetTbwWrittenTb(), 0.0);

    EXPECT_TRUE(ssd.ReadData(50.0));
    EXPECT_FALSE(ssd.ReadData(200.0));
    EXPECT_FALSE(ssd.ReadData(-1.0));
}

TEST(SSDTest, StorageOutOfSpaceException) {
    SSD ssd("Crucial P3", "NVMe", 500, 150.0);
    EXPECT_TRUE(ssd.WriteData(400.0));
    EXPECT_THROW(ssd.WriteData(200.0), StorageOutOfSpaceException);
}

TEST(SSDTest, TrimAndLifespanEstimation) {
    SSD ssd("Crucial MX500", "SATA 3", 500, 180.0);
    ssd.WriteData(20.0);
    ssd.PerformTrim();
    EXPECT_EQ(ssd.GetUsedGb(), 18);

    double months = ssd.EstimateRemainingLifespanMonths(50.0);
    EXPECT_GT(months, 0.0);

    double idle_months = ssd.EstimateRemainingLifespanMonths(0.0);
    EXPECT_DOUBLE_EQ(idle_months, 120.0);
}

TEST(SSDTest, EqualityAndStream) {
    SSD s1("Model A", "NVMe", 1000);
    SSD s2("Model A", "NVMe", 1000);
    SSD s3("Model B", "SATA", 500);

    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s1 != s3);

    std::stringstream ss;
    ss << s1;
    EXPECT_NE(ss.str().find("SSD: Model A"), std::string::npos);
}