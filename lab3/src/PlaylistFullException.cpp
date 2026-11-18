/**
 * @file PlaylistFullException.cpp
 * @brief Implementation of PlaylistFullException exception.
 * @author Nikita Momot
 * @date 2026
 */

#include "PlaylistFullException.h"

PlaylistFullException::PlaylistFullException(const std::string& message)
    : MusicPlayerException(message) {}