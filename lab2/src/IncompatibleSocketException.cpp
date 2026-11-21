/**
 * @file IncompatibleSocketException.cpp
 * @brief Implementation of IncompatibleSocketException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "IncompatibleSocketException.h"

IncompatibleSocketException::IncompatibleSocketException(const std::string& message) :
    ComputerException("IncompatibleSocketException: " + message) {}