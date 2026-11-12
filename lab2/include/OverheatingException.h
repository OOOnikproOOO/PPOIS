/**
 * @file OverheatingException.h
 * @brief Declaration of the OverheatingException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef OVERHEATINGEXCEPTION_H
#define OVERHEATINGEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when component temperature exceeds the maximum safe limit (TJMax).
 */
class OverheatingException : public ComputerException {
public:
    /**
     * @brief Constructs a new OverheatingException with an error message.
     * @param message Detailed error description.
     */
    explicit OverheatingException(const std::string& message);
};

#endif