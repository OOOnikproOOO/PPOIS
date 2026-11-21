/**
 * @file UnauthorizedPlaybackException.h
 * @brief Declaration of UnauthorizedPlaybackException exception.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef UNAUTHORIZEDPLAYBACKEXCEPTION_H
#define UNAUTHORIZEDPLAYBACKEXCEPTION_H

#include "MusicPlayerException.h"

/**
 * @brief Thrown when UnauthorizedPlaybackException condition occurs.
 */
class UnauthorizedPlaybackException : public MusicPlayerException {
public:
    explicit UnauthorizedPlaybackException(const std::string& message);
};

#endif