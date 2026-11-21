/**
 * @file POSTFailureException.cpp
 * @brief Implementation of POSTFailureException methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "POSTFailureException.h"

POSTFailureException::POSTFailureException(const std::string& message) :
    ComputerException("POSTFailureException: " + message) {}