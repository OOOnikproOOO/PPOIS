/**
 * @file OverheatingException.cpp
 * @brief Implementation of OverheatingException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "OverheatingException.h"

OverheatingException::OverheatingException(const std::string& message) :
    ComputerException("OverheatingException: " + message) {}