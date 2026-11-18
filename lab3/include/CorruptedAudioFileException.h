/**
 * @file CorruptedAudioFileException.h
 * @brief Declaration of CorruptedAudioFileException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef CORRUPTEDAUDIOFILEEXCEPTION_H
#define CORRUPTEDAUDIOFILEEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when CorruptedAudioFileException condition occurs.
 */
class CorruptedAudioFileException : public MusicPlayerException {
public:
    explicit CorruptedAudioFileException(const std::string& message);
};

#endif