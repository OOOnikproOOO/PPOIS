/**
 * @file StorageBadSectorException.cpp
 * @brief Implementation of StorageBadSectorException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "StorageBadSectorException.h"

StorageBadSectorException::StorageBadSectorException(const std::string& message) :
    ComputerException("StorageBadSectorException: " + message) {}