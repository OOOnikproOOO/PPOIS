/**
 * @file ThermalThrottlingException.cpp
 * @brief Implementation of ThermalThrottlingException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ThermalThrottlingException.h"

ThermalThrottlingException::ThermalThrottlingException(const std::string& message) :
    ComputerException("ThermalThrottlingException: " + message) {}