/**
 * @file test_exceptions.cpp
 * @brief Модульные тесты для классов исключений предметной области "Компьютер".
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include "Exceptions.h"

TEST(ExceptionsTest, ComputerExceptionHierarchy) {
    try {
        throw DeviceNotFoundException("PCIe device at slot 1 not responding");
    } catch (const ComputerException& ex) {
        EXPECT_NE(std::string(ex.what()).find("DeviceNotFoundException"), std::string::npos);
    }
}

TEST(ExceptionsTest, ThermalAndPowerExceptions) {
    EXPECT_THROW(throw ThermalThrottlingException("CPU temperature 95C"), ThermalThrottlingException);
    EXPECT_THROW(throw OverheatingException("CPU temperature 105C exceeds TJMax"), OverheatingException);
    EXPECT_THROW(throw PowerSupplyOverloadException("Power draw 850W exceeds 750W PSU"), PowerSupplyOverloadException);
    EXPECT_THROW(throw VoltageInstabilityException("12V rail dropped to 10.8V"), VoltageInstabilityException);
}

TEST(ExceptionsTest, MemoryAndStorageExceptions) {
    EXPECT_THROW(throw IncompatibleSocketException("LGA1700 CPU in AM5 socket"), IncompatibleSocketException);
    EXPECT_THROW(throw IncompatibleMemoryException("DDR4 stick in DDR5 slot"), IncompatibleMemoryException);
    EXPECT_THROW(throw MemoryAllocationException("Out of RAM"), MemoryAllocationException);
    EXPECT_THROW(throw StorageOutOfSpaceException("Disk full"), StorageOutOfSpaceException);
    EXPECT_THROW(throw StorageBadSectorException("NAND block corrupted"), StorageBadSectorException);
    EXPECT_THROW(throw POSTFailureException("RAM self-test failed"), POSTFailureException);
}