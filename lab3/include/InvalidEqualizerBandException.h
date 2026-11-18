/**
 * @file InvalidEqualizerBandException.h
 * @brief Declaration of InvalidEqualizerBandException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef INVALIDEQUALIZERBANDEXCEPTION_H
#define INVALIDEQUALIZERBANDEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when InvalidEqualizerBandException condition occurs.
 */
class InvalidEqualizerBandException : public MusicPlayerException {
public:
    explicit InvalidEqualizerBandException(const std::string& message);
};

#endif