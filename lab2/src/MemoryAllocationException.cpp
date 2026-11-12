/**
 * @file MemoryAllocationException.cpp
 * @brief Implementation of MemoryAllocationException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "MemoryAllocationException.h"

MemoryAllocationException::MemoryAllocationException(const std::string& message) :
    ComputerException("MemoryAllocationException: " + message) {}