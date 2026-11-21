/**
 * @file POSTFailureException.h
 * @brief Declaration of the POSTFailureException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef POSTFAILUREEXCEPTION_H
#define POSTFAILUREEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when Power-On Self-Test (POST) detects critical hardware failures.
 */
class POSTFailureException : public ComputerException {
public:
    /**
     * @brief Constructs a new POSTFailureException with an error message.
     * @param message Detailed error description.
     */
    explicit POSTFailureException(const std::string& message);
};

#endif