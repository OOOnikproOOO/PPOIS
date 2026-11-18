/**
 * @file LicenseExpiredException.cpp
 * @brief Implementation of LicenseExpiredException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "LicenseExpiredException.h"

LicenseExpiredException::LicenseExpiredException(const std::string& message)
    : MusicPlayerException(message) {}