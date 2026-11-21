/**
 * @file IncompatibleSocketException.h
 * @brief Declaration of the IncompatibleSocketException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef INCOMPATIBLESOCKETEXCEPTION_H
#define INCOMPATIBLESOCKETEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when a CPU socket is incompatible with the motherboard.
 */
class IncompatibleSocketException : public ComputerException {
public:
    /**
     * @brief Constructs a new IncompatibleSocketException with an error message.
     * @param message Detailed error description.
     */
    explicit IncompatibleSocketException(const std::string& message);
};

#endif