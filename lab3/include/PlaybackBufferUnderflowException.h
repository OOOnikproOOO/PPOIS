/**
 * @file PlaybackBufferUnderflowException.h
 * @brief Declaration of PlaybackBufferUnderflowException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYBACKBUFFERUNDERFLOWEXCEPTION_H
#define PLAYBACKBUFFERUNDERFLOWEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when PlaybackBufferUnderflowException condition occurs.
 */
class PlaybackBufferUnderflowException : public MusicPlayerException {
public:
    explicit PlaybackBufferUnderflowException(const std::string& message);
};

#endif