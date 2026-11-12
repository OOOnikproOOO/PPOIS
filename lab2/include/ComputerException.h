/**
 * @file ComputerException.h
 * @brief Declaration of the ComputerException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H

#include <stdexcept>
#include <string>

/**
 * @brief Base class for all computer system hardware and software exceptions.
 */
class ComputerException : public std::runtime_error {
public:
    /**
     * @brief Constructs a new ComputerException with an error message.
     * @param message Detailed error description.
     */
    explicit ComputerException(const std::string& message);
};

#endif