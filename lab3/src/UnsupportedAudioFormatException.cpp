/**
 * @file UnsupportedAudioFormatException.cpp
 * @brief Implementation of UnsupportedAudioFormatException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "UnsupportedAudioFormatException.h"

UnsupportedAudioFormatException::UnsupportedAudioFormatException(const std::string& message)
    : MusicPlayerException(message) {}