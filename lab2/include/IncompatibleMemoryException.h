/**
 * @file IncompatibleMemoryException.h
 * @brief Declaration of the IncompatibleMemoryException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef INCOMPATIBLEMEMORYEXCEPTION_H
#define INCOMPATIBLEMEMORYEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when memory type or generation is incompatible with the slot.
 */
class IncompatibleMemoryException : public ComputerException {
public:
    /**
     * @brief Constructs a new IncompatibleMemoryException with an error message.
     * @param message Detailed error description.
     */
    explicit IncompatibleMemoryException(const std::string& message);
};

#endif