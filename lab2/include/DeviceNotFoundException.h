/**
 * @file DeviceNotFoundException.h
 * @brief Declaration of the DeviceNotFoundException class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef DEVICENOTFOUNDEXCEPTION_H
#define DEVICENOTFOUNDEXCEPTION_H

#include <string>
#include "ComputerException.h"

/**
 * @brief Exception thrown when an accessed device is not connected or not found.
 */
class DeviceNotFoundException : public ComputerException {
public:
    /**
     * @brief Constructs a new DeviceNotFoundException with an error message.
     * @param message Detailed error description.
     */
    explicit DeviceNotFoundException(const std::string& message);
};

#endif