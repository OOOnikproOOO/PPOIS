/**
 * @file StorageBadSectorException.h
 * @brief Declaration of the StorageBadSectorException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef STORAGEBADSECTOREXCEPTION_H
#define STORAGEBADSECTOREXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when corrupted sectors or failing flash memory cells are encountered.
 */
class StorageBadSectorException : public ComputerException {
public:
    /**
     * @brief Constructs a new StorageBadSectorException with an error message.
     * @param message Detailed error description.
     */
    explicit StorageBadSectorException(const std::string& message);
};

#endif