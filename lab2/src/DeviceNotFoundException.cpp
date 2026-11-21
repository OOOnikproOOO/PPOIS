/**
 * @file DeviceNotFoundException.cpp
 * @brief Implementation of DeviceNotFoundException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "DeviceNotFoundException.h"

DeviceNotFoundException::DeviceNotFoundException(const std::string& message) :
    ComputerException("DeviceNotFoundException: " + message) {}