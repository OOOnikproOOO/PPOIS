/**
 * @file PowerSupplyOverloadException.cpp
 * @brief Implementation of PowerSupplyOverloadException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PowerSupplyOverloadException.h"

PowerSupplyOverloadException::PowerSupplyOverloadException(const std::string& message) :
    ComputerException("PowerSupplyOverloadException: " + message) {}