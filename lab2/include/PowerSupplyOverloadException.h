/**
 * @file PowerSupplyOverloadException.h
 * @brief Declaration of the PowerSupplyOverloadException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef POWERSUPPLYOVERLOADEXCEPTION_H
#define POWERSUPPLYOVERLOADEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when system power draw exceeds the power supply rating.
 */
class PowerSupplyOverloadException : public ComputerException {
public:
    /**
     * @brief Constructs a new PowerSupplyOverloadException with an error message.
     * @param message Detailed error description.
     */
    explicit PowerSupplyOverloadException(const std::string& message);
};

#endif