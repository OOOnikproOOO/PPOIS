/**
 * @file IncompatibleMemoryException.cpp
 * @brief Implementation of IncompatibleMemoryException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "IncompatibleMemoryException.h"

IncompatibleMemoryException::IncompatibleMemoryException(const std::string& message) :
    ComputerException("IncompatibleMemoryException: " + message) {}