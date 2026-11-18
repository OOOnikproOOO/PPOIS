/**
 * @file UnsupportedAudioFormatException.h
 * @brief Declaration of UnsupportedAudioFormatException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef UNSUPPORTEDAUDIOFORMATEXCEPTION_H
#define UNSUPPORTEDAUDIOFORMATEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when UnsupportedAudioFormatException condition occurs.
 */
class UnsupportedAudioFormatException : public MusicPlayerException {
public:
    explicit UnsupportedAudioFormatException(const std::string& message);
};

#endif