/**
 * @file PlaylistFullException.h
 * @brief Declaration of PlaylistFullException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYLISTFULLEXCEPTION_H
#define PLAYLISTFULLEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when PlaylistFullException condition occurs.
 */
class PlaylistFullException : public MusicPlayerException {
public:
    explicit PlaylistFullException(const std::string& message);
};

#endif