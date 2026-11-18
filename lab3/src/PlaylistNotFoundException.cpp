/**
 * @file PlaylistNotFoundException.cpp
 * @brief Implementation of PlaylistNotFoundException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "PlaylistNotFoundException.h"

PlaylistNotFoundException::PlaylistNotFoundException(const std::string& message)
    : MusicPlayerException(message) {}