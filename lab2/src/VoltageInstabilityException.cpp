/**
 * @file VoltageInstabilityException.cpp
 * @brief Implementation of VoltageInstabilityException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "VoltageInstabilityException.h"

VoltageInstabilityException::VoltageInstabilityException(const std::string& message) :
    ComputerException("VoltageInstabilityException: " + message) {}