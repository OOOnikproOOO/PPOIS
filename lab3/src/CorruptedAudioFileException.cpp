/**
 * @file CorruptedAudioFileException.cpp
 * @brief Implementation of CorruptedAudioFileException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "CorruptedAudioFileException.h"

CorruptedAudioFileException::CorruptedAudioFileException(const std::string& message)
    : MusicPlayerException(message) {}