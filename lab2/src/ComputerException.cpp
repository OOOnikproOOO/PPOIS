/**
 * @file ComputerException.cpp
 * @brief Implementation of ComputerException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ComputerException.h"

ComputerException::ComputerException(const std::string& message) : std::runtime_error(message) {}