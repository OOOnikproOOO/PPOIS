/**
 * @file PlaybackBufferUnderflowException.cpp
 * @brief Implementation of PlaybackBufferUnderflowException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "PlaybackBufferUnderflowException.h"

PlaybackBufferUnderflowException::PlaybackBufferUnderflowException(const std::string& message)
    : MusicPlayerException(message) {}