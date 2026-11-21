/**
 * @file ThermalThrottlingException.h
 * @brief Declaration of the ThermalThrottlingException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef THERMALTHROTTLINGEXCEPTION_H
#define THERMALTHROTTLINGEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when thermal throttling occurs due to high temperatures.
 */
class ThermalThrottlingException : public ComputerException {
public:
    /**
     * @brief Constructs a new ThermalThrottlingException with an error message.
     * @param message Detailed error description.
     */
    explicit ThermalThrottlingException(const std::string& message);
};

#endif