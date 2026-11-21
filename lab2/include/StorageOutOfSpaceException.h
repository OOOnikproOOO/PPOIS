/**
 * @file StorageOutOfSpaceException.h
 * @brief Declaration of the StorageOutOfSpaceException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef STORAGEOUTOFSPACEEXCEPTION_H
#define STORAGEOUTOFSPACEEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when write operations fail due to a lack of free storage space.
 */
class StorageOutOfSpaceException : public ComputerException {
public:
    /**
     * @brief Constructs a new StorageOutOfSpaceException with an error message.
     * @param message Detailed error description.
     */
    explicit StorageOutOfSpaceException(const std::string& message);
};

#endif