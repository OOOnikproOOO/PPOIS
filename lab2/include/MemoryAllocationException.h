/**
 * @file MemoryAllocationException.h
 * @brief Declaration of the MemoryAllocationException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MEMORYALLOCATIONEXCEPTION_H
#define MEMORYALLOCATIONEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when RAM allocation fails due to memory exhaustion.
 */
class MemoryAllocationException : public ComputerException {
public:
    /**
     * @brief Constructs a new MemoryAllocationException with an error message.
     * @param message Detailed error description.
     */
    explicit MemoryAllocationException(const std::string& message);
};

#endif