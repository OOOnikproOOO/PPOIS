/**
 * @file test_storage_controller.cpp
 * @brief Unit tests for the StorageController class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "StorageController.h"
#include "ComputerException.h"

TEST(StorageControllerTest, ConstructorAndGetters) {
    StorageController controller("Intel RST NVMe");
    EXPECT_EQ(controller.GetControllerType(), "Intel RST NVMe");
    EXPECT_EQ(controller.GetRaidMode(), "NONE");
    EXPECT_EQ(controller.GetSsdCount(), 0);
    EXPECT_EQ(controller.GetHddCount(), 0);
    EXPECT_TRUE(controller.IsRaidHealthy());
    EXPECT_DOUBLE_EQ(controller.GetTotalCapacityGb(), 0.0);
}

TEST(StorageControllerTest, AttachDrivesAndCapacityCalculation) {
    StorageController controller;
    controller.AttachSSD(SSD("SSD1", "NVMe", 1000));
    controller.AttachHDD(HDD("HDD1", 7200, 2000));

    EXPECT_EQ(controller.GetSsdCount(), 1);
    EXPECT_EQ(controller.GetHddCount(), 1);
    EXPECT_DOUBLE_EQ(controller.GetTotalCapacityGb(), 3000.0);

    controller.ConfigureRAID("RAID1");
    EXPECT_EQ(controller.GetRaidMode(), "RAID1");
    EXPECT_DOUBLE_EQ(controller.GetTotalCapacityGb(), 1500.0);
}

TEST(StorageControllerTest, RAIDConfigurationExceptions) {
    StorageController controller;
    EXPECT_THROW(controller.ConfigureRAID("INVALID_RAID"), ComputerException);
    EXPECT_THROW(controller.ConfigureRAID("RAID0"), ComputerException);

    controller.AttachSSD(SSD("SSD1", "NVMe", 500));
    EXPECT_THROW(controller.ConfigureRAID("RAID1"), ComputerException);

    controller.AttachSSD(SSD("SSD2", "NVMe", 500));
    EXPECT_NO_THROW(controller.ConfigureRAID("RAID0"));
    EXPECT_NO_THROW(controller.ConfigureRAID("JBOD"));
    EXPECT_NO_THROW(controller.ConfigureRAID("NONE"));
}

TEST(StorageControllerTest, IntegrityCheckFailingDrives) {
    StorageController controller;
    SSD failing_ssd("Old SSD", "SATA", 256, 0.05);
    failing_ssd.WriteData(100.0);
    failing_ssd.RunHealthCheck();

    controller.AttachSSD(failing_ssd);
    EXPECT_FALSE(controller.PerformIntegrityCheck());
    EXPECT_FALSE(controller.IsRaidHealthy());
}

TEST(StorageControllerTest, EqualityAndStream) {
    StorageController c1("Type A");
    StorageController c2("Type A");
    StorageController c3("Type B");

    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c1 != c3);

    std::stringstream ss;
    ss << c1;
    EXPECT_NE(ss.str().find("Storage Controller"), std::string::npos);
}