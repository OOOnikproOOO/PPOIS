/**
 * @file VoltageInstabilityException.h
 * @brief Declaration of the VoltageInstabilityException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef VOLTAGEINSTABILITYEXCEPTION_H
#define VOLTAGEINSTABILITYEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when voltage on power rails falls outside the ATX standard tolerance.
 */
class VoltageInstabilityException : public ComputerException {
public:
    /**
     * @brief Constructs a new VoltageInstabilityException with an error message.
     * @param message Detailed error description.
     */
    explicit VoltageInstabilityException(const std::string& message);
};

#endif