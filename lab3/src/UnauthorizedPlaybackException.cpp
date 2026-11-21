/**
 * @file UnauthorizedPlaybackException.cpp
 * @brief Implementation of UnauthorizedPlaybackException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "UnauthorizedPlaybackException.h"

UnauthorizedPlaybackException::UnauthorizedPlaybackException(const std::string& message)
    : MusicPlayerException(message) {}