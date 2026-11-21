/**
 * @file PlaylistNotFoundException.h
 * @brief Declaration of PlaylistNotFoundException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLAYLISTNOTFOUNDEXCEPTION_H
#define PLAYLISTNOTFOUNDEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when PlaylistNotFoundException condition occurs.
 */
class PlaylistNotFoundException : public MusicPlayerException {
public:
    explicit PlaylistNotFoundException(const std::string& message);
};

#endif