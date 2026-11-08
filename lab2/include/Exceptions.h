/**
 * @file Exceptions.h
 * @brief Custom exception classes for the Computer domain.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

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
    explicit ComputerException(const std::string& message) : std::runtime_error(message) {}
};

/**
 * @brief Exception thrown when an accessed device is not connected or not found.
 */
class DeviceNotFoundException : public ComputerException {
public:
    explicit DeviceNotFoundException(const std::string& message) : ComputerException("DeviceNotFoundException: " + message) {}
};

/**
 * @brief Exception thrown when a CPU socket is incompatible with the motherboard.
 */
class IncompatibleSocketException : public ComputerException {
public:
    explicit IncompatibleSocketException(const std::string& message) : ComputerException("IncompatibleSocketException: " + message) {}
};

/**
 * @brief Exception thrown when memory type or generation is incompatible with the slot.
 */
class IncompatibleMemoryException : public ComputerException {
public:
    explicit IncompatibleMemoryException(const std::string& message) : ComputerException("IncompatibleMemoryException: " + message) {}
};

/**
 * @brief Exception thrown when thermal throttling occurs due to high temperatures.
 */
class ThermalThrottlingException : public ComputerException {
public:
    explicit ThermalThrottlingException(const std::string& message) : ComputerException("ThermalThrottlingException: " + message) {}
};

/**
 * @brief Exception thrown when component temperature exceeds the maximum safe limit (TJMax).
 */
class OverheatingException : public ComputerException {
public:
    explicit OverheatingException(const std::string& message) : ComputerException("OverheatingException: " + message) {}
};

/**
 * @brief Exception thrown when system power draw exceeds the power supply rating.
 */
class PowerSupplyOverloadException : public ComputerException {
public:
    explicit PowerSupplyOverloadException(const std::string& message) : ComputerException("PowerSupplyOverloadException: " + message) {}
};

/**
 * @brief Exception thrown when voltage on power rails falls outside the ATX standard tolerance.
 */
class VoltageInstabilityException : public ComputerException {
public:
    explicit VoltageInstabilityException(const std::string& message) : ComputerException("VoltageInstabilityException: " + message) {}
};

/**
 * @brief Exception thrown when write operations fail due to a lack of free storage space.
 */
class StorageOutOfSpaceException : public ComputerException {
public:
    explicit StorageOutOfSpaceException(const std::string& message) : ComputerException("StorageOutOfSpaceException: " + message) {}
};

/**
 * @brief Exception thrown when corrupted sectors or failing flash memory cells are encountered.
 */
class StorageBadSectorException : public ComputerException {
public:
    explicit StorageBadSectorException(const std::string& message) : ComputerException("StorageBadSectorException: " + message) {}
};

/**
 * @brief Exception thrown when RAM allocation fails due to memory exhaustion.
 */
class MemoryAllocationException : public ComputerException {
public:
    explicit MemoryAllocationException(const std::string& message) : ComputerException("MemoryAllocationException: " + message) {}
};

/**
 * @brief Exception thrown when Power-On Self-Test (POST) detects critical hardware failures.
 */
class POSTFailureException : public ComputerException {
public:
    explicit POSTFailureException(const std::string& message) : ComputerException("POSTFailureException: " + message) {}
};

#endif