/**
 * @file LicenseExpiredException.h
 * @brief Declaration of LicenseExpiredException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef LICENSEEXPIREDEXCEPTION_H
#define LICENSEEXPIREDEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when LicenseExpiredException condition occurs.
 */
class LicenseExpiredException : public MusicPlayerException {
public:
    explicit LicenseExpiredException(const std::string& message);
};

#endif