/**
 * @file StorageOutOfSpaceException.cpp
 * @brief Implementation of StorageOutOfSpaceException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "StorageOutOfSpaceException.h"

StorageOutOfSpaceException::StorageOutOfSpaceException(const std::string& message) :
    ComputerException("StorageOutOfSpaceException: " + message) {}