/**
 * @file test_hdd.cpp
 * @brief Unit tests for the HDD class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "HDD.h"
#include "StorageOutOfSpaceException.h"
#include "StorageBadSectorException.h"

TEST(HDDTest, ConstructorAndGetters) {
    HDD hdd("Seagate Barracuda", 7200, 2000, 256);
    EXPECT_EQ(hdd.GetModel(), "Seagate Barracuda");
    EXPECT_EQ(hdd.GetRpm(), 7200);
    EXPECT_EQ(hdd.GetCapacityGb(), 2000);
    EXPECT_EQ(hdd.GetUsedGb(), 0);
    EXPECT_EQ(hdd.GetFreeSpaceGb(), 2000);
    EXPECT_EQ(hdd.GetCacheMb(), 256);
    EXPECT_TRUE(hdd.AreHeadsParked());
    EXPECT_EQ(hdd.GetBadSectorsCount(), 0);
}

TEST(HDDTest, ParkAndSpinUp) {
    HDD hdd;
    hdd.SpinUp();
    EXPECT_FALSE(hdd.AreHeadsParked());
    hdd.ParkHeads();
    EXPECT_TRUE(hdd.AreHeadsParked());
}

TEST(HDDTest, WriteReadAndBadSectorScan) {
    HDD hdd("WD Blue", 5400, 1000);
    EXPECT_FALSE(hdd.WriteData(0.0));
    EXPECT_TRUE(hdd.WriteData(250.0));
    EXPECT_FALSE(hdd.AreHeadsParked());
    EXPECT_EQ(hdd.GetUsedGb(), 250);

    EXPECT_TRUE(hdd.ReadData(100.0));
    EXPECT_FALSE(hdd.ReadData(500.0));

    hdd.ScanForBadSectors(300000);
    EXPECT_EQ(hdd.GetBadSectorsCount(), 3);
}

TEST(HDDTest, StorageOutOfSpaceException) {
    HDD hdd("Toshiba P300", 7200, 500);
    EXPECT_TRUE(hdd.WriteData(400.0));
    EXPECT_THROW(hdd.WriteData(200.0), StorageOutOfSpaceException);
}

TEST(HDDTest, StorageBadSectorException) {
    HDD hdd("Failing Drive", 5400, 1000);
    hdd.ScanForBadSectors(15000000);
    EXPECT_GE(hdd.GetBadSectorsCount(), 100);
    EXPECT_THROW(hdd.WriteData(10.0), StorageBadSectorException);
}

TEST(HDDTest, EqualityAndStream) {
    HDD h1("Disk 1", 7200, 1000);
    HDD h2("Disk 1", 7200, 1000);
    HDD h3("Disk 2", 5400, 2000);

    EXPECT_TRUE(h1 == h2);
    EXPECT_TRUE(h1 != h3);

    std::stringstream ss;
    ss << h1;
    EXPECT_NE(ss.str().find("HDD: Disk 1"), std::string::npos);
}